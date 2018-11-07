#include "Miner.h"
#include "../blockchain_algorithm/Verifier.h"
#include "../blockchain_network/BlockchainContext.h"

void Miner::
_init(void) {

	/* Estado inicial */
	nextBlockBuffer.clear();
	currBlockBuffer.clear();
	miningBlock.clear();
	miningState = MiningState::WAITING_TX;
}

void Miner::
_change_miner_status(Miner::Status newStatus) {

	_change_status((unsigned int)newStatus);
}

Miner::
Miner(void) : FullService() {

	/* Inicializacion */
	_init();
}

Miner::
Miner(ECDSA<ECP, SHA256>::PrivateKey privateKey) : FullService(privateKey){

	/* Inicializacion */
	_init();
}

Miner::
Miner(const Miner& copy) : FullService(copy){

	/* Copia de elementos */
	nextBlockBuffer = copy.nextBlockBuffer;
	currBlockBuffer = copy.currBlockBuffer;
	miningBlock = copy.miningBlock;
	miningState = copy.miningState;
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
	miningBlock = copy.miningBlock;
	miningState = copy.miningState;

	return *this;
}

unsigned int Miner::
getType(void) {

	return MINER_TYPE;
}

void Miner::
_receive_message() {

	/* Verifico que haya llegado algun mensaje */
	BlockchainMessage msg;
	if (getNextMessage(msg)) {

		/* Segun el tipo de mensaje */
		switch (msg.getType()) {

		case BlockchainMessage::Type::BLOCKCHAIN_REQUEST:
			if ((Status)status != Status::SYNC_BLOCKCHAIN) {
				BlockchainMessage newMsg(BlockchainMessage::Type::BLOCKCHAIN, storage);
				sendAll(newMsg);
			}
			break;

		case BlockchainMessage::Type::NEW_TRANSACTION:
			if ((Status)status != Status::SYNC_BLOCKCHAIN)
				_add_transaction(msg.getTransaction());
			break;

		case BlockchainMessage::Type::MINED_BLOCK:
			if ((Status)status != Status::SYNC_BLOCKCHAIN)
				_add_block(msg.getBlock());
			break;

		case BlockchainMessage::Type::BLOCKCHAIN:
			if ((Status)status == Status::SYNC_BLOCKCHAIN)
				_sync_node(msg.getBlockchain());

		default:
			if ((Status)status != Status::MINING_BLOCK && (Status)status != Status::SYNC_BLOCKCHAIN)
				(Status::PENDING_MSG);
			break;
		}
	}
	else {

		if ((Status)status != Status::MINING_BLOCK)
			_change_miner_status(Status::IDLE);
	}
}

void Miner::
_send_message() {
	if ((Status)status != Status::SYNC_BLOCKCHAIN) {

		/* Mando algun mensaje */
		if (!toSendQueue.empty()) {

			BlockchainMessage msg = toSendQueue.front();

			/* Intento mandarlo */
			sendAll(msg);

			/* Lo agrego a los mios */
			_add_transaction(msg.getTransaction());

			/* Lo elimino */
			toSendQueue.pop_front();
		}
	}
}

void Miner::
_process_data() {

	/* Me fijo si estoy minando */
	if ((Status)status == Status::MINING_BLOCK) {

		/* Segun el estado */
		switch (miningState) {

		case MiningState::PREPARE_BLOCK:
			_prepare_block();
			break;

		case MiningState::TRY_NONCE:
			_try_nonce();
			break;

		case MiningState::SEND_BLOCK:
			_send_block();
			break;

		default:
			miningState = MiningState::PREPARE_BLOCK;
			break;
		}

	}
	else if ((Status)status != Status::SYNC_BLOCKCHAIN) {
		/* Me fijo si hay transacciones para minar */
		if (!currBlockBuffer.empty()) {

			/* Cambio a minar */
			_change_miner_status(Status::MINING_BLOCK);
			miningState = MiningState::PREPARE_BLOCK;
		}
	}
}

void Miner::
_prepare_block(void) {

	list<Block> blockchain;
	storage.getBlockchain(blockchain);

	/* Creamos el bloque */
	Block block(publicKey, BlockchainContext::getMinerFee());

	/* Configuramos */
	block.setPrevBlock(blockchain.back());
	block.setTimestamp();

	/* Agrego transacciones */
	for (Transaction tx : currBlockBuffer) {

		block.addTransaction(tx);
	}

	/* Guardo */
	miningBlock = block;

	/* Cambio estado */
	miningState = MiningState::TRY_NONCE;
	nonce.clear();
}

void Miner::
_add_transaction(Transaction transaction) {

	/* Verifico que no este en ninguna ya */
	list<Transaction>::iterator itr;

	itr = find(nextBlockBuffer.begin(), nextBlockBuffer.end(), transaction);

	if (itr == nextBlockBuffer.end()) {

		itr = find(currBlockBuffer.begin(), currBlockBuffer.end(), transaction);

		if (itr == currBlockBuffer.end()) {

			/* Le agrego la comision del minero */
			Transaction newTx = _add_fee(transaction);

			/* La guardo */
			if ((Status)status == Status::MINING_BLOCK) {
				nextBlockBuffer.push_back(newTx);
			}
			else {
				currBlockBuffer.push_back(newTx);
			}
		}
	}

}

Transaction Miner::
_add_fee(Transaction transaction) {

	/* Me fijo si hay una diferencia sobrante */
	if (Verifier::validateTransaction(storage.getUTXO(), transaction)) {
	
		/* Busco la cantidad */
		double tip = Verifier::getMinerTip(storage.getUTXO(), transaction);

		/* Si hay, la agrego */
		Output output;
		output.setOutput(tip, publicKey);

		/* Nueva transaccion */
		transaction.addOutput(output);
		transaction.hash();
	}

	return transaction;
}

void Miner::
_add_block(Block block) {

	list<Block> blockchain;
	storage.getBlockchain(blockchain);
	
	/* Verifico si es correcto */
	if (Verifier::validateBlock(blockchain, storage.getUTXO(), block)) {

		/* Lo agrego a la blockchain */
		storage.addBlock(block);

		/* Reacomodo todas las transacciones */
		_reset_buffer(block);

		/* Me fijo en que estado */
		if ((Status)status == Status::MINING_BLOCK) {


			/* Dejo de minar */
			_change_miner_status(Status::PENDING_MSG);
		}
	}
	else {

		/* Reviso si alguna version vieja de la blockchain era valida */
		unsigned int tries = blockchain.size() > 5 ? 5 : blockchain.size() - 1;
		list<Block>::reverse_iterator itr = blockchain.rbegin();

		while (tries) {

			/* Me fijo si esta es valida */
			if ( itr->getPrevHash() == block.getPrevHash() ) {

				/* Pido sincronizacion */
				_set_sync_mode();
				break;
			}

			/* Descuento el intento de version vieja */
			tries--;
			itr++;
		}
	}
}

void Miner::
_reset_buffer(Block block) {

	list<Transaction>::iterator itr;

	/* Busco las transacciones en el bloque repetidas */
	for (Transaction tx : block.getTransactions()) {

		itr = find(nextBlockBuffer.begin(), nextBlockBuffer.end(), tx);
		if (itr != nextBlockBuffer.end()) {

			nextBlockBuffer.erase(itr);
		}
		itr = find(currBlockBuffer.begin(), currBlockBuffer.end(), tx);
		if (itr != currBlockBuffer.end()) {


			currBlockBuffer.erase(itr);
		}
	}

	/* Todas a curr */
	for (Transaction tx : nextBlockBuffer) {

		currBlockBuffer.push_back(tx);
	}
	nextBlockBuffer.clear();

}

void Miner::
_try_nonce(void) {

	/* Saco un valor aleatorio */
	unsigned int tryNonce;
	do {

		/* Aleatorio */
		tryNonce = rand() * rand();
		
	}while ( find(nonce.begin(), nonce.end(), tryNonce) != nonce.end());

	/* Lo agrego a la lista de usado */
	nonce.push_back(tryNonce);

	/* Con el valor actual de nonce pruebo */
	miningBlock.setNonce(tryNonce);
	miningBlock.hash();

	/* Obtengo el hash */
	string hash = miningBlock.getCurrHash();
	if (BlockchainContext::validatePOW(hash)) {

		/* Gane cambio de estado */
		miningState = MiningState::SEND_BLOCK;
	}
}

void Miner::
_send_block(void) {

	/* Guardo el bloque en mi blockchain */
	storage.addBlock(miningBlock);

	/* Se lo mando a todos */
	BlockchainMessage msg(BlockchainMessage::Type::MINED_BLOCK, miningBlock);
	sendAll(msg);

	/* Cambio de estado */
	miningState = MiningState::WAITING_TX;
	_change_miner_status(Status::PENDING_MSG);

	/* Limpio y guardo */
	currBlockBuffer = nextBlockBuffer;
	nextBlockBuffer.clear();
}

void Miner::
_sync_node(BlockchainStorage blockchain) {

	storage = blockchain;

	nextBlockBuffer.clear();
	currBlockBuffer.clear();

	_change_miner_status(Status::IDLE);
}

void Miner::
_set_sync_mode(void) {

	/* Cambio a modo sincronizar */
	_change_miner_status(Status::SYNC_BLOCKCHAIN);

	/* Mando mensaje de sincronizacion */
	BlockchainMessage msg(BlockchainMessage::Type::BLOCKCHAIN_REQUEST);
	sendAll(msg);
}