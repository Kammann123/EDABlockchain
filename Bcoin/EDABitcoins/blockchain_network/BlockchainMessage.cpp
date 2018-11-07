#include "BlockchainMessage.h"

BlockchainMessage::
BlockchainMessage(void) {

	/* Nothing to do */
}

BlockchainMessage::
BlockchainMessage(Type type, BlockchainStorage blockchain) {

	this->type = type;
	this->blockchain = blockchain;
}

BlockchainMessage::
BlockchainMessage(Type type, ECDSA<ECP, SHA256>::PublicKey publicKey) {

	this->type = type;
	this->nodeKey = publicKey;
}

BlockchainMessage::
BlockchainMessage(Type type) {

	this->type = type;
}

BlockchainMessage::
BlockchainMessage(Type type, string detail) {

	this->type = type;
	this->detail = detail;
}

BlockchainMessage::
BlockchainMessage(Type type, Block block) {

	this->type = type;
	this->block = block;
}

BlockchainMessage::
BlockchainMessage(Type type, Transaction transaction) {

	this->type = type;
	this->transaction = transaction;
}

BlockchainMessage::
BlockchainMessage(const BlockchainMessage& copy) {

	this->type = copy.type;
	this->detail = copy.detail;
	this->block = copy.block;
	this->transaction = copy.transaction;
	this->blockchain = copy.blockchain;
}

BlockchainMessage::
~BlockchainMessage() {

	/* Nothing to do */
}

bool BlockchainMessage::
operator==(const BlockchainMessage& op) {

	/* Si son del mismo tipo */
	if (op.type == type) {

		/* Verifico segun el tipo */
		switch (type) {

			case Type::NEW_TRANSACTION:
				return transaction == op.transaction;
				break;
			case Type::MINED_BLOCK:
				return block == op.block;
				break;
			case Type::BLOCKCHAIN:
				return blockchain == op.blockchain;
				break;
			case Type::BLOCKCHAIN_REQUEST:
				return nodeKey == op.nodeKey;
				break;
		}
	}
	
	return false;
}

bool BlockchainMessage::
operator!=(const BlockchainMessage& op) {

	return !(*this == op);
}

const BlockchainMessage& BlockchainMessage::
operator=(const BlockchainMessage& op) {

	/* Copio los elementos */
	this->detail = op.detail;
	this->type = op.type;
	this->block = op.block;
	this->transaction = op.transaction;
	this->blockchain = op.blockchain;

	return *this;
}

void BlockchainMessage::
setType(Type type) {

	this->type = type;
}

void BlockchainMessage::
setDetail(string detail) {

	this->detail = detail;
}

void BlockchainMessage::
setBlock(Block block) {

	this->block = block;
}

void BlockchainMessage::
setTransaction(Transaction transaction) {

	this->transaction = transaction;
}

BlockchainMessage::Type BlockchainMessage::
getType(void) const {

	return type;
}

string BlockchainMessage::
getDetail(void) const {

	return detail;
}

Block BlockchainMessage::
getBlock(void) const {

	return block;
}

Transaction BlockchainMessage::
getTransaction(void) const {

	return transaction;
}

BlockchainStorage BlockchainMessage::
getBlockchain(void) const {

	return blockchain;
}

void BlockchainMessage::
setBlockchain(BlockchainStorage blockchain) {

	this->blockchain = blockchain;
}