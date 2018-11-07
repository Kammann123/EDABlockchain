#include "Block.h"
#include "cryptoeda.h"

#include <time.h>

Block::
Block(void) {

	/* Valores por defecto */
	currHash = "";
	prevHash = "";
	timestamp = 0;
	nonce = 0;
}

Block::
Block(ECDSA<ECP, SHA256>::PublicKey publicKey, double amount) {

	/* Valores por defecto */
	currHash = "";
	prevHash = "";
	timestamp = 0;
	nonce = 0;

	/* Agrego transaccion de minero */
	this->setReward(publicKey, amount);
}

Block::
Block(const Block& copy) {

	/* Copio los elementos del bloque */
	currHash = copy.currHash;
	prevHash = copy.prevHash;
	timestamp = copy.timestamp;
	nonce = copy.nonce;
	transactions = copy.transactions;
}

Block::
~Block() {

	/* Nothing to do */
}

void Block::
setPrevBlock(string prevHash) {
	
	this->prevHash = prevHash;
}

bool Block::
operator==(const Block& copy) {

	/* Verifico si los dos bloque son iguales */
	return this->currHash == copy.currHash;
}

const Block& Block::
operator=(const Block& copy) {

		/* Copio los elementos del bloque */
		currHash = copy.currHash;
		prevHash = copy.prevHash;
		timestamp = copy.timestamp;
		nonce = copy.nonce;
		transactions = copy.transactions;

		return *this;
}

void Block::
clear(void) {

	/* Limpio los contenidos */
	currHash = "";
	prevHash = "";
	timestamp = 0;
	nonce = 0;
	transactions.clear();
}

bool Block::
clear(ECDSA<ECP, SHA256>::PublicKey publicKey, double amount) {

	/* Limpio el bloque */
	this->clear();

	/* Agrego la transaccion inicial del minero */
	return this->setReward(publicKey, amount);
}

bool Block::
setReward(ECDSA<ECP, SHA256>::PublicKey publicKey, double amount) {

	/* Creo la transaccion */
	Transaction transaction;
	transaction.addOutput(Output(amount, publicKey));
	transaction.setTimestamp();
	transaction.hash();

	/* Agrego la transaccion */
	try {

		transactions.push_front(transaction);
		return true;
	}
	catch (...) {

		return false;
	}
}

void Block::
setPrevBlock(const Block& prevBlock) {

	/* Configuro el hash */
	this->prevHash = prevBlock.currHash;
}

void Block::
setTimestamp(void) {

	/* Configuro el timestamp */
	this->timestamp = (int)time(NULL);
}

void Block::
setNonce(unsigned int nonce) {

	/* Configuro el valor del nonce */
	this->nonce = nonce;
}

bool Block::
addTransaction(const Transaction& tx) {

	/* Agrego una transaccion */
	try {
		transactions.push_back(tx);

		return true;
	}
	catch (...) {

		return false;
	}
}

bool Block::
removeTransaction(const Transaction& tx) {

	/* Remuevo la transaccion */
	try {

		transactions.remove(tx);

		return true;
	}
	catch (...) {

		return false;
	}
}

void Block::
hash(void) {

	string body = dataBody();

	/* Guardo el hash */
	currHash = cryptoeda::hash(body);
}

string Block::
dataBody(void) const {

	/* Busco el cuerpo del bloque */
	string body = prevHash
		+ to_string(timestamp)
		+ to_string(nonce);

	/* El numero del transacciones */
	body += to_string(transactions.size());

	/* Busco las transacciones */
	for (Transaction tx : transactions) {

		body += tx.body();
	}

	return body;
}

void Block::
setHash(string hash) {

	this->currHash = hash;
}

string Block::
getCurrHash(void) const {

	return currHash;
}

string Block::
getPrevHash(void) const {

	return prevHash;
}

unsigned int Block::
getTimestamp(void) const {

	return timestamp;
}

unsigned int Block::
getNonce(void) const {

	return nonce;
}

list<Transaction> Block::
getTransactions(void) const {

	return transactions;
}

bool Block::
validateHash(void) {

	/* Obtengo el body */
	string body = dataBody();

	string hash = cryptoeda::hash(body);

	return hash == this->currHash;
}

string Block::
body(void) const {

	string body = currHash
		+ dataBody();

	return body;
}