#pragma once

#include "../blockchain/Block.h"
#include "../blockchain/UTXO.h"
#include "../blockchain/cryptoeda.h"

#include <list>
#include <string>

using namespace std;

/*
* BlockchainStorage
*
* Esta clase implemente y administra el almacenamiento de la 
* blockchain, regulando que entra y que no dentro de la misma.
*/
class BlockchainStorage {

public:

	/*
	* Constructores y destructores de la blockchain
	*/
	BlockchainStorage(void);
	BlockchainStorage(const BlockchainStorage& copy);
	BlockchainStorage(list<Block>& blockchain);
	BlockchainStorage(list<Block>& blockchain, list<UTXO>& utxos);
	~BlockchainStorage(void);

	/*
	* Sobrecarga de operadores
	*/
	bool operator==(const BlockchainStorage& cpy);

	/*
	* oldVersion
	*
	* Devuelve un almacenamiento de la blockchain de una version vieja
	* segun el hash del que debe ser el ultimo bloque!
	*/
	bool oldVersion(string hash, BlockchainStorage& storage);

	/*
	* addBlock
	*
	* Agrego un bloque a la blockchain, en caso de ser validado,
	* luego devuelve true, si falla devuelve false.
	*
	* block: Bloque para agregar
	*/
	bool addBlock(Block block);

	/*
	* restaureBlockchain
	*
	* Vuelve y restaura estados previos de la blockchain,
	* volviendo atras segun como se llame al metodo.
	*
	* block: Primer bloque desde donde se debe eliminar
	*/
	bool restaureBlockchain(void);
	bool restaureBlockchain(Block block);

	/*
	* getBlockchain
	*
	* Devuelve true si pudo obtener la blockchain.
	* 
	* blockchain: Donde guarda la lista de blockchain.
	* block: Hasta que bloque recupera
	*/
	bool getBlockchain(list<Block>& blockchain);
	bool getBlockchain(list<Block>& blockchain, Block& block);

	/*
	* getUTXO
	*
	* Devuelve la lista de transacciones no gastadas de la blockchain.
	*/
	list<UTXO>& getUTXO(void);

	/*
	* updateUTXO
	*
	* Actualiza el estado de la lista de UTXO en base al contenido
	* de la blockchain con respecto a aquellas transacciones no gastadas.
	*
	*/
	void updateUTXO(string hash, unsigned int index);
	void updateUTXO(void);
	void updateUTXO(UTXO& utxo);
	void updateUTXO(Transaction& transaction);
	void updateUTXO(Block& block);

protected:

	list<Block> blockchain;
	list<UTXO> utxos;
};