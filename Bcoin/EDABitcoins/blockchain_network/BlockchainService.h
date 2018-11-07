#pragma once

#include "../blockchain/cryptoeda.h"
#include "../blockchain/UTXO.h"

#include "BlockchainMessage.h"

#include <list>

using namespace std;

/*
* BlockchainService
*
* Esta clase administra los servicios que se pueden ejecutar sobre la
* blockchain para los usuarios, como peticion de balances o emision de
* nuevas transacciones entre usuarios. Se debe ejecutar sobre un nodo
* con almacenamiento de la blockchain, por si sola no registra la misma.
*/
class BlockchainService {

public:

	/*
	* Constructores y destructores de BlockchainService
	*/
	BlockchainService(list<UTXO>& _utxos);
	~BlockchainService(void);

	/*
	* Sobrecarga de operadores
	*/
	const BlockchainService& operator=(const BlockchainService& copy);

	/*
	* fetchBalance
	*
	* Devuelve el balance actual del usuario.
	*
	* publicKey: Clave publica del usuario
	*/
	double fetchBalance(ECDSA<ECP, SHA256>::PublicKey publicKey);

	/*
	* fetchUTXOS
	*
	* Devuelve el listado de transacciones no gastadas del usuario.
	*
	* publicKey: Clave publica del usuario
	*/
	list<UTXO> fetchUTXOS(ECDSA<ECP, SHA256>::PublicKey publicKey);

	/*
	* createTransaction
	*
	* Crea una nueva transaccion desde un usuario a otro con la
	* cantidad de monedas y la comision para el minero dada.
	*
	* from, to: Quien y para quien
	* amount: Cantidad a transferir
	* minerFee: Lo que se le paga al minero
	* newTransaction: Donde se guarda la nueva transaccion
	*/
	bool createTransaction(
		ECDSA<ECP, SHA256>::PublicKey from,
		ECDSA<ECP, SHA256>::PublicKey to,
		double amount,
		double minerFee,
		Transaction& newTransaction
	);
	
	/*
	* createTransactionMessage
	*
	* Crea un nuevo mensaje de transaccion para mandar a los nodos.
	*
	* transaction: Transaccion ya creada.
	* privateKey: Si desea firmarla.
	*/
	BlockchainMessage createTransactionMessage(Transaction transaction);
	BlockchainMessage createTransactionMessage(
		Transaction transaction,
		ECDSA<ECP, SHA256>::PrivateKey privateKey
	);

private:

	/*
	* getAmount
	*
	* Calcula el valor acumulado por un listado de UTXO
	*
	* utxos: Listado de transacciones de salida
	*/
	double getAmount(list<UTXO>& utxos);

	list<UTXO>& utxos;
};