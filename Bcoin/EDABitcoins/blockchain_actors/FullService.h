#pragma once

#include "../blockchain_network/BlockchainNode.h"
#include "../blockchain_network/BlockchainStorage.h"
#include "../blockchain_network/BlockchainService.h"
#include "../Subject.h"
#include <deque>

using namespace std;

#define FULLSERVICE_TYPE 0

/*
* FullService
*
* Modelizacion de un nodo FullService de la red peer to peer.
* Tiene la capacidad de ejecutar servicios y almacenar la blockchain.
*/
class FullService : public BlockchainNode{

public:

	/*
	* Estados del run
	*/
	enum class RunState : unsigned int {
		RECEIVE_MSG,
		SEND_MSG,
		PROCESS_DATA
	};

	/*
	* Estados de operacion del FullService
	*/
	enum class Status : unsigned int {
		IDLE,
		PENDING_MSG,
		PROCESS_MSG
	};

	/*
	* Constructores y destructores del FullService
	*/
	FullService(void);
	FullService(ECDSA<ECP, SHA256>::PrivateKey privateKey);
	FullService(const FullService& copy);
	~FullService(void);

	/*
	* Sobrecarga de operadores
	*/
	const FullService& operator=(const FullService& copy);

	/*
	*
	* transfer
	*
	* Realiza una transferencia por la red peer to peer.
	* Si devuelve true, la pudo mandar con exito!
	*
	* from, to: Claves publicas de remitente y destinatario
	* sign: Clave privada para pagar
	* amount, fee: Cuanto se transfiere y se deja al minero
	*/
	bool transfer(
		ECDSA<ECP, SHA256>::PublicKey from,
		ECDSA<ECP, SHA256>::PublicKey to,
		ECDSA<ECP, SHA256>::PrivateKey sign,
		double amount,
		double fee
	);
	bool transfer(
		ECDSA<ECP, SHA256>::PublicKey from,
		ECDSA<ECP, SHA256>::PublicKey to,
		double amount,
		double fee
	);

	/*
	*
	* genesis
	* 
	* Crea y manda el bloque genesis.
	*
	* publicKey: A quien lo manda.
	* amount: Valor inicio
	*/
	bool genesis(ECDSA<ECP, SHA256>::PublicKey publicKey, double amount);
	bool genesis(double amount);

	/*
	*
	* balance
	*
	* Devuelve el balance actual del usuario de la red.
	*
	* publicKey: Clave publica del usuario.
	*/
	double balance(ECDSA<ECP, SHA256>::PublicKey publicKey);

	/*
	*
	* run
	*
	* Ejecuta una operacion de FullService.
	*/
	void run(void);

	/*
	*
	* getBlockchain
	*
	* Devuelve la blockchain
	*/
	list<Block> getBlockchain(void);

	/*
	*
	* getUTXOS
	*
	* Devuelve la lista de transacciones no gastadas
	*/
	list<UTXO> getUTXOS(void);

	/*
	*
	* isSelected - toggleSelection
	*
	* Ven y modifican el estado de seleccion del nodo FullService
	*/
	bool isSelected(void);
	void toggleSelection(void);

	/*
	*
	* getType
	*
	* Devuelve el tipo FullService
	*/
	virtual unsigned int getType(void);

protected:

	/*
	* Inicializacion
	*/
	void _init(void);

	/*
	* Cambio de estado y aviso o actualizo
	*/
	void _change_fullservice_status(FullService::Status newStatus);

	/*
	* Rutinas de ejecucion del nodo
	*/
	virtual void _receive_message(void);
	virtual void _send_message(void);
	virtual void _process_data(void);

	BlockchainStorage storage;
	BlockchainService service;
	RunState runState;
	bool selected;
};