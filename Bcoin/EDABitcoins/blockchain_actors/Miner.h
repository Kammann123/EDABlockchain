#pragma once

#include "FullService.h"
#include "MinerEvent.h"
#include "MinerFsm.h"

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
	* Estados de operacion del minero 
	*/
	enum class Status : unsigned int {
		IDLE,
		MINING,
		SYNC
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

	/*
	* addBlock
	*
	* Intenta agregar un bloque a la blockchain y si detecta
	* que el bloque es correcto pero la blockchain esta mal,
	* entonces devuelve False.
	* Ademas, una vez que agrega el bloque, actualiza el estado de
	* las transacciones.
	*
	* block: Bloque para agregar
	*/
	bool addBlock(Block& block);
	bool addBlock(Block& block, bool& continueMining);

	/*
	* addNextTransaction
	*
	* Agrega una nueva transaccion a las proximas a minar
	*/
	void addNextTransaction(Transaction& transaction);

	/*
	* addCurrTransaction
	*
	* Agrega una nueva transaccion a la que va a minar
	*/
	void addCurrTransaction(Transaction& transaction);

	/*
	* sendBlockchain
	*
	* Manda un mensaje a la red con la blockchain
	*/
	void sendBlockchain(void);

	/*
	* tryStartMining
	*
	* Verifica si hay suficientes condiciones para iniciar a minar,
	* y devuelve True si las hay
	*/
	bool tryStartMining(void);

	/*
	* prepareCurrBlock
	*
	* Arma el bloque con las transacciones actuales para minar.
	* Previo a ello, converge todas las transacciones en curr.
	*
	*/
	Block prepareCurrBlock(void);

	/*
	* sendBlock
	*
	* Manda el bloque minado a la red peer to peer.
	* Cuando termina de mandarlo, actualiza el estado de las 
	* transacciones en lista pendiente para minar.
	*/
	void sendBlock(Block& block);

	/*
	* sendBlockchainRequest
	*
	* Manda una peticion de blockchain para la red peer to peer
	*/
	void sendBlockchainRequest(void);

	/*
	* syncBlockchain
	*
	* Sincroniza el estado actual de la blockchain, y limpia
	* el contenido de las listas de transacciones, dejando unicamente
	* las que no fueron utilizadas hasta ahora.
	*/
	void syncBlockchain(BlockchainStorage& blockchain);

	/*
	* updateTransactions
	*
	* Converge todas las transacciones no procesadas en una sola
	* lista para minarlas a continuacion y luego elimina aquellas
	* que ya fueron procesadas en la blockchain.
	*/
	void updateTransactions(void);

	/*
	* addFee
	*
	* Agrego la comision para el minero!
	*/
	void addFee(Transaction& transaction);

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

	list<Transaction> nextBlockBuffer;
	list<Transaction> currBlockBuffer;
	MinerFsm minerFsm;
};