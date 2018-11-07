#pragma once

#include <string>

#include "BlockchainStorage.h"
#include "../blockchain/Block.h"
#include "../blockchain/Transaction.h"

using namespace std;

/*
* BlockchainMessage
*
* La idea de esta clase es modelar los mensajes comunicados a traves de la red
* peer to peer del blockchain para establecer aquellos objetos que se comunican de
* nodos a nodos de una forma mas clara.
*/
class BlockchainMessage {

public:

	/*
	* Tipos de mensajes a transmitir en la red
	*/
	enum class Type : unsigned int {
		NEW_TRANSACTION,
		MINED_BLOCK,
		BLOCKCHAIN,
		BLOCKCHAIN_REQUEST
	};

	/*
	* Constructores y destructores de Blockchain Message
	*/
	BlockchainMessage(void);
	BlockchainMessage(Type type);
	BlockchainMessage(Type type, ECDSA<ECP, SHA256>::PublicKey publicKey);
	BlockchainMessage(Type type, string detail);
	BlockchainMessage(Type type, Block block);
	BlockchainMessage(Type type, BlockchainStorage blockchain);
	BlockchainMessage(Type type, Transaction transaction);
	BlockchainMessage(const BlockchainMessage& copy);
	~BlockchainMessage();

	/*
	* Sobrecarga de operadores 
	*/
	bool operator==(const BlockchainMessage& op);
	bool operator!=(const BlockchainMessage& op);
	const BlockchainMessage& operator=(const BlockchainMessage& op);

	/*
	* Setters de los parametros
	*/
	void setType(Type type);
	void setDetail(string detail);
	void setBlock(Block block);
	void setTransaction(Transaction transaction);
	void setBlockchain(BlockchainStorage blockchain);

	/*
	* Getters de los parametros
	*/
	Type getType(void) const;
	string getDetail(void) const;
	Block getBlock(void) const;
	Transaction getTransaction(void) const;
	BlockchainStorage getBlockchain(void) const;

protected:
	
	string detail;
	Type type;
	Block block;
	Transaction transaction;
	BlockchainStorage blockchain;
	ECDSA<ECP, SHA256>::PublicKey nodeKey;
};