#include "FullService.h"

#include "../blockchain_algorithm/Verifier.h"

void FullService::
_init(void) {

	/* Estado inicial */
	selected = false;
	status = (unsigned int)FullService::Status::IDLE;
	runState = FullService::RunState::RECEIVE_MSG;
}

void FullService::
_change_fullservice_status(FullService::Status newStatus) {

	/* Cambio el estado */
	if ((FullService::Status)status != newStatus) {
		_change_status((unsigned int)newStatus);
	}
}

FullService::
FullService(void) : BlockchainNode(), storage(), service(storage.getUTXO()){

	/* Estado inicial */
	_init();
}

FullService::
FullService(ECDSA<ECP, SHA256>::PrivateKey privateKey) : BlockchainNode(privateKey), storage(), service(storage.getUTXO()) {

	/* Estado inicial */
	_init();
}

FullService::
FullService(const FullService& copy) : BlockchainNode(), storage(), service(storage.getUTXO()){

	/* Copo los elementos */
	storage = copy.storage;
	service = copy.service;
	status = copy.status;
	selected = copy.selected;
	runState = copy.runState;
}

FullService::
~FullService(void) {

	/* Nothing to do */
}

const FullService& FullService::
operator=(const FullService& copy) {

	/* Copo los elementos */
	storage = copy.storage;
	service = copy.service;
	status = copy.status;
	selected = copy.selected;

	return *this;
}

bool FullService::
transfer(
	ECDSA<ECP, SHA256>::PublicKey from,
	ECDSA<ECP, SHA256>::PublicKey to,
	ECDSA<ECP, SHA256>::PrivateKey sign,
	double amount,
	double fee) {

	/* Creo la transaccion */
	Transaction transaction;

	if (service.createTransaction(from, to, amount, fee, transaction)) {

		if (transaction.validateHash()) {

			/* Firmo y creo el mensaje */
			BlockchainMessage msg = service.createTransactionMessage(transaction, privateKey);

			sendBuffer(msg);
		}

		return true;
	}
	else {

		/* No se pudo crear la transaccion */
		return false;
	}
}

bool FullService::
transfer(
	ECDSA<ECP, SHA256>::PublicKey from,
	ECDSA<ECP, SHA256>::PublicKey to,
	double amount,
	double fee) {

	/* Creo la transaccion */
	Transaction transaction;

	if (service.createTransaction(from, to, amount, fee, transaction)) {

		/* Firmo y creo el mensaje */
		BlockchainMessage msg = service.createTransactionMessage(transaction);

		sendBuffer(msg);

		return true;
	}
	else {

		/* No se pudo crear la transaccion */
		return false;
	}
}

double FullService::
balance(ECDSA<ECP, SHA256>::PublicKey publicKey) {

	/* Busco el valor en la UTXO */
	double amount = service.fetchBalance(publicKey);

	return amount;
}

list<Block> FullService::
getBlockchain(void) {

	list<Block> blockchain;

	storage.getBlockchain(blockchain);

	return blockchain;
}

list<UTXO> FullService::
getUTXOS(void) {

	return storage.getUTXO();
}

bool FullService::
isSelected(void) {

	return selected;
}

void FullService::
toggleSelection(void) {

	selected = selected ? false : true;

	_change_status();
}

unsigned int FullService::
getType(void) {

	return FULLSERVICE_TYPE;
}

void FullService::
run(void) {
	
	/* Segun el estado */
	switch (runState) {

		case RunState::RECEIVE_MSG:
			_receive_message();

			runState = RunState::SEND_MSG;
			break;

		case RunState::SEND_MSG:
			_send_message();

			runState = RunState::PROCESS_DATA;
			break;

		case RunState::PROCESS_DATA:
			_process_data();

			runState = RunState::RECEIVE_MSG;
			break;

		default:
			runState = RunState::RECEIVE_MSG;
			break;
	}
}

void FullService::
_receive_message(void) {

	/* Verifico si hay mensaje*/
	BlockchainMessage msg; 
	BlockchainMessage nMsg;
	if (getNextMessage(msg)) {

		/* Veo si me importa o no */
		switch (msg.getType()) {

			case BlockchainMessage::Type::BLOCKCHAIN_REQUEST:

				/* Armo y guardo el mensaje */
				nMsg.setType(BlockchainMessage::Type::BLOCKCHAIN);
				nMsg.setBlockchain(storage);
				sendBuffer(nMsg);

				break;

			case BlockchainMessage::Type::MINED_BLOCK:

				if (storage.addBlock(msg.getBlock())) {

					_change_fullservice_status(Status::PROCESS_MSG);
				}
				else {

					_change_fullservice_status(Status::PENDING_MSG);
				}
				break;

			default:
				_change_fullservice_status(Status::PENDING_MSG);
				break;
		}
	}
	else {

		_change_fullservice_status(Status::IDLE);
	}
}

void FullService::
_send_message(void) {

	/* Mando algun mensaje */
	release();
}

void FullService::
_process_data(void) {

	/* Nothing to do */
}

bool FullService::
genesis(double amount) {

	return genesis(publicKey, amount);
}

bool FullService::
genesis(ECDSA<ECP, SHA256>::PublicKey publicKey, double amount) {

	/* Creo el bloque */
	Block block = Verifier::genesisBlock(publicKey, amount);

	/* Verifico que no haya ya bloque genesis */
	list<Block> blockchain;
	storage.getBlockchain(blockchain);
	if (blockchain.empty()) {
	
		/* Agrego el bloque */
		storage.addBlock(block);

		/* Mando mensaje */
		BlockchainMessage msg(BlockchainMessage::Type::MINED_BLOCK, block);
		sendBuffer(msg);

		return true;
	}

	return false;
}