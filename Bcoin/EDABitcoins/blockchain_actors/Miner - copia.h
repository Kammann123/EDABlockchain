#pragma once

#include "FullService.h"
#include <list>

#define MINER_TYPE	1

using namespace std;

/*
* Miner
* 
* Modelizacion de un nodo Minero de la red peer to peer con las funciones
* como cualquier full service para realizar operaciones y transacciones,
* almacenar la blockchain, y de forma distinguida, minar bloques.
*/
class Miner : public FullService {

public:
	
	/*
	* Estados del minado
	*/
	enum class MiningState : unsigned int {
		WAITING_TX,
		PREPARE_BLOCK,
		TRY_NONCE,
		SEND_BLOCK
	};

	/*
	* Estados de operacion del minero 
	*/
	enum class Status : unsigned int {
		IDLE,
		PENDING_MSG,
		MINING_BLOCK,
		SYNC_BLOCKCHAIN
	};

	/*
	* Constructores y destructores del Miner
	*/
	Miner(void);
	Miner(ECDSA<ECP, SHA256>::PrivateKey privateKey);
	Miner(const Miner& copy);
	~Miner(void);

	/*
	* Sobrecarga de operadores
	*/
	const Miner& operator=(const Miner& copy);

	/*
	* 
	* getType
	*
	* Devuelve el tipo de dato Minero
	*/
	virtual unsigned int getType(void);

protected:

	/*
	* Inicializacion
	*/
	void _init(void);
	void _change_miner_status(Miner::Status newStatus);

	/*
	* Rutinas de ejecucion del nodo
	*/
	virtual void _receive_message(void);
	virtual void _send_message(void);
	virtual void _process_data(void);
	
	void _add_transaction(Transaction transaction);
	Transaction _add_fee(Transaction transaction);

	void _add_block(Block block);
	void _reset_buffer(Block block);

	/*
	* Rutinas para minar 
	*/
	void _prepare_block(void);
	void _try_nonce(void);
	void _send_block(void);

	void _sync_node(BlockchainStorage blockchain);
	void _set_sync_mode(void);

	list<Transaction> nextBlockBuffer;
	list<Transaction> currBlockBuffer;
	Block miningBlock;
	MiningState miningState;
	list<unsigned int> nonce;
};