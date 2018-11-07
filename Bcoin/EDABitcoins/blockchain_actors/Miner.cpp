#include "Miner.h"
#include "../blockchain_algorithm/Verifier.h"
#include "../blockchain_network/BlockchainContext.h"

void Miner::
_init(void) {

	/* Estado inicial */
	nextBlockBuffer.clear();
	currBlockBuffer.clear();
	minerFsm.reset();
}

void Miner::
_change_miner_status(Miner::Status newStatus) {

	if ((Miner::Status)status != newStatus) {

		_change_status((unsigned int)newStatus);
	}
}

Miner::
Miner(void) : FullService() , minerFsm(*this) {

	/* Inicializacion */
	_init();
}

Miner::
Miner(ECDSA<ECP, SHA256>::PrivateKey privateKey) : FullService(privateKey), minerFsm(*this) {

	/* Inicializacion */
	_init();
}

Miner::
Miner(const Miner& copy) : FullService(copy), minerFsm(*this) {

	/* Copia de elementos */
	nextBlockBuffer = copy.nextBlockBuffer;
	currBlockBuffer = copy.currBlockBuffer;
	minerFsm = copy.minerFsm;
}

Miner::
~Miner(void) {

	/* Nothing to do */
}

const Miner& Miner::
operator=(const Miner& copy) {

	FullService* self = this;
	*self = copy;

	/* Copia de elementos */
	nextBlockBuffer = copy.nextBlockBuffer;
	currBlockBuffer = copy.currBlockBuffer;
	minerFsm = copy.minerFsm;

	return *this;
}

unsigned int Miner::
getType(void) {

	return MINER_TYPE;
}

void Miner::
_receive_message() {

	/* Busco si hay mensajes */
	BlockchainMessage msg;
	if (getNextMessage(msg)) {

		/* Armo un evento */
		MinerEvent event(MinerEvent::Type::COMMUNICATION, msg);
		minerFsm.runEvent(event);
	}

}

void Miner::
_send_message() {

	if (!msgBuffer.empty()) {

		/* Me quedo con el mensaje para ver si es transaccion */
		BlockchainMessage msg = msgBuffer.front();

		/* Creo y mando un evento */
		if (msg.getType() == BlockchainMessage::Type::NEW_TRANSACTION) {

			MinerEvent event(MinerEvent::Type::COMMUNICATION, msg);
			minerFsm.runEvent(event);
		}
	}

	/* Release */
	release();
}

void Miner::
_process_data() {

/* Armo el evento */
MinerEvent event(MinerEvent::Type::PROCESS);

/* Mando el evento */
minerFsm.runEvent(event);
}

void Miner::
updateTransactions(void) {

	/* Agrego todas las proximas a las actuales y limpio */
	for (Transaction tx : nextBlockBuffer) {
		currBlockBuffer.push_back(tx);
	}
	nextBlockBuffer.clear();

	/* Reviso que no esten ya en la blockchain */
	list<Block> blockchain;
	storage.getBlockchain(blockchain);

	for (Block block : blockchain) {

		for (Transaction tx : block.getTransactions()) {

			/* Si la encuentro entre las mias, la remuevo */
			if (find(currBlockBuffer.begin(), currBlockBuffer.end(), tx) != currBlockBuffer.end()) {

				currBlockBuffer.remove(tx);
			}
		}
	}
}

void Miner::
syncBlockchain(BlockchainStorage& blockchain) {

	/* Guardo la blockchain */
	storage = blockchain;

	/* Actualizo contenido de transacciones */
	updateTransactions();
}

void Miner::
sendBlockchainRequest(void) {

	/* Armo el mensaje de request */
	BlockchainMessage msg(BlockchainMessage::Type::BLOCKCHAIN_REQUEST, this->publicKey);

	/* Mando el mensaje */
	sendBuffer(msg);
}

void Miner::
sendBlock(Block& block) {

	/* Armo y envio el mensaje */
	BlockchainMessage msg(BlockchainMessage::Type::MINED_BLOCK, block);
	sendBuffer(msg);

	/* Agrego a mi blockchain */
	addBlock(block);
}

void Miner::
addNextTransaction(Transaction& transaction) {

	/* Valido transaccion */
	if (Verifier::validateTransaction(storage.getUTXO(), transaction)) {

		addFee(transaction);

		/* Verifico que no este ya agregada */
		if (find(nextBlockBuffer.begin(), nextBlockBuffer.end(), transaction) == nextBlockBuffer.end()) {

			/* Agrego a la proxima */
			nextBlockBuffer.push_back(transaction);
		}
	}
}

void Miner::
addFee(Transaction& transaction) {
	/* Busco la cantidad */
	double tip = Verifier::getMinerTip(storage.getUTXO(), transaction);

	/* Si hay, la agrego */
	Output output;
	output.setOutput(tip, publicKey);

	/* Nueva transaccion */
	transaction.addOutput(output);
	transaction.hash();
}

void Miner::
addCurrTransaction(Transaction& transaction) {

	/* Valido transaccion */
	if (Verifier::validateTransaction(storage.getUTXO(), transaction)) {

		addFee(transaction);

		/* Que no este ya adentro */
		if (find(currBlockBuffer.begin(), currBlockBuffer.end(), transaction) == currBlockBuffer.end()){

			/* Agrego a la actual */
			currBlockBuffer.push_back(transaction);
		}
	}
}

bool Miner::
tryStartMining(void) {

	/* Verifico cantidad de curr transactions */
	if (currBlockBuffer.size()) {

		return true;
	}
	else {

		return false;
	}
}

void Miner::
sendBlockchain(void) {

	/* Armo el mensaje y lo envio */
	BlockchainMessage msg(BlockchainMessage::Type::BLOCKCHAIN, storage);
	sendBuffer(msg);
}

Block Miner::
prepareCurrBlock(void) {
	list<Block> blockchain;
	storage.getBlockchain(blockchain);

	/* Actualizo transacciones */
	updateTransactions();

	/* Creo el nuevo bloque */
	Block block(publicKey, BlockchainContext::getMinerFee());

	/* Configuramos el nuevo bloque */
	block.setPrevBlock(blockchain.back());
	block.setTimestamp();

	/* Agrego transacciones */
	for (Transaction tx : currBlockBuffer) {

		block.addTransaction(tx);
	}

	return block;
}

bool Miner::
addBlock(Block& block, bool& continueMining) {
	list<Block> blockchain;
	storage.getBlockchain(blockchain);

	/* Verifico si es correcto el bloque */
	if (Verifier::validateBlock(blockchain, storage.getUTXO(), block)) {

		/* Lo agrego a la blockchain */
		storage.addBlock(block);

		/* Reacomodo todas las transacciones */
		updateTransactions();

		continueMining = false;
		return true;
	}
	else {

		BlockchainStorage oldStorage;

		if (storage.oldVersion(block.getPrevHash(), oldStorage)) {

			list<Block> oldBlockchain;
			oldStorage.getBlockchain(oldBlockchain);

			if (Verifier::validateBlock(oldBlockchain, oldStorage.getUTXO(), block)) {


				/* Pido sincronizacion */
				continueMining = false;
				return false;
			}
		}
	}

	continueMining = true;
	return true;
}

bool Miner::
addBlock(Block& block) {

	bool buff;

	return addBlock(block, buff);
}