#pragma once

#include <string>
#include <list>

#include "Transaction.h"
#include "cryptoeda.h"

using namespace std;

/*
* Block
* Esta clase almacena la informacion de un bloque dentro de la 
* blockchain y luego tiene metodos para poder trabajar sobre este tanto
* en su almacenamiento, como verificacion y minado
*/
class Block {

public:

	/*
	* Constructores y destructores de Block
	*/
	Block();
	Block(ECDSA<ECP, SHA256>::PublicKey publicKey, double amount);
	Block(const Block& copy);
	~Block();

	/* 
	* Sobrecarga de operadores con Block
	*/
	bool operator==(const Block& copy);
	const Block& operator=(const Block& copy);

	/* 
	* clear
	* Limpia el objeto Block
	*/
	void clear(void);
	bool clear(ECDSA<ECP, SHA256>::PublicKey publicKey, double amount);

	/*
	* setReward
	*
	* Configura una primera transaccion en el bloque que contiene
	* el premio por haber minado tal bloque para dicho minero.
	*
	* publicKey: Clave publica del minero
	* amount: Monedas minadas
	*/
	bool setReward(ECDSA<ECP, SHA256>::PublicKey publicKey, double amount);

	/*
	* setPrevBlock
	* Configura la vinculacion con el bloque anterior del blockchain
	*
	* prevBlock: Bloque previo/anterior
	*/
	void setPrevBlock(const Block& prevBlock);
	void setPrevBlock(string prevHash);

	/*
	* setTimestamp
	* Establece el timestamp actual en el momento del llamado
	*/
	void setTimestamp(void);

	/*
	* setNonce
	* Establece el valor del nonce
	*
	* nonce: Valor a configurar
	*/
	void setNonce(unsigned int nonce);

	/*
	* addTransaction
	* Agrega una transaccion al bloque
	*
	* tx: Nueva transaccion al bloque 
	*/
	bool addTransaction(const Transaction& tx);

	/*
	* removeTransaction
	* Remueve una transaccion del bloque
	*
	* tx: Transaccion a remover
	*/
	bool removeTransaction(const Transaction& tx);

	/*
	* hash
	* Calcula el hash del estado actual del bloque
	*/
	void hash(void);

	/*
	* setHash
	* Configura el valor actual del hash
	*/
	void setHash(string hash);

	/*
	* getCurrHash
	* Devuelve el hash del bloque actual
	*/
	string getCurrHash(void) const;

	/*
	* getPrevHash
	* Devuelve el hash del bloque anterior
	*/
	string getPrevHash(void) const;

	/* 
	* getTimestamp
	* Devuelve el timestamp del bloque
	*/
	unsigned int getTimestamp(void) const;

	/*
	* getNonce
	* Devuelvo el valor del nonce del bloque
	*/
	unsigned int getNonce(void) const;
	
	/* 
	* getTransactions
	* Devuelve la lista de transacciones del bloque
	*/
	list<Transaction> getTransactions(void) const;

	/*
	* validateHash
	* Devuelve true si es correcto el hashing del bloque
	*/
	bool validateHash(void);

	/*
	* body
	* Devuelve el string con el cuerpo del bloque
	*/
	string body(void) const;

private:

	/*
	* dataBody
	* String con el cuerpo del bloque sin su hash
	*/
	string dataBody(void) const;

	string currHash;
	string prevHash;
	unsigned int timestamp;
	unsigned int nonce;
	list<Transaction> transactions;
};