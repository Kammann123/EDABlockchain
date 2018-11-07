#pragma once

#include "../blockchain/UTXO.h"
#include "../blockchain/Transaction.h"
#include "../blockchain/Block.h"
#include "../blockchain/Output.h"

#include <list>
#include <string>

using namespace std;

/*
* Verifier
* 
* Su funcion es la de contener las diferentes funciones que realizan las 
* validaciones y verificaciones sobre objetos de la blockchain para
* saber cuando algo esta bien o mal. 
*/
namespace Verifier {

	/*
	* validateTransaction
	*
	* Valida una transaccion a realizarse dentro de la blockchain.
	*
	* utxos: Listado con las transacciones de salida no gastadas
	* transaction: Transaccion a realizar
	*/
	bool validateTransaction(list<UTXO>& utxos, Transaction& transaction);

	/*
	* validateBlock
	* 
	* Valida un bloque para ser agregado como bloque minado correctamente
	*
	* blockchain: Lista de bloques
	* utxos: Listado de las transacciones de salida no gastadas
	* block: Bloque a validar
	*/
	bool validateBlock(list<Block>& blockchain, list<UTXO>& utxos, Block& block);

	/*
	* utxoWasSpent
	*
	* Verifica si fue gastada o no la UTXO detro de la blockchain
	*
	* blockchain: Cadena de bloques
	* utxo: Transaccion
	*/
	bool utxoWasSpent(list<Block>& blockchain, UTXO utxo);

	/*
	* getMinerTip
	* 
	* Devuelve la diferencia entre lo que sale y lo que entra de la transaccion
	*
	* utxos: Lista de transacciones salientes no gastadas
	* transaction: Transaccion en cuestion
	*/
	double getMinerTip(list<UTXO>& utxos, Transaction& transaction);

	/*
	* searchOutput
	*
	* Devuelve true si encontro la output.
	*
	* utxos: Transacciones donde busca la output
	* hashID: Hash de la transaccion
	* index: Indice de la output a buscar
	* output: Donde se guarda el resultado 
	*/
	bool searchOutput(list<UTXO>& utxos, string hashID, unsigned int index, Output& output);

	/*
	* searchTransaction
	*
	* Busca y se fija si la transaccion esta dentro de la UTXO
	*
	* utxos: Lista de transacciones no gastadas
	* transaction: Transaccion
	*/
	bool searchTransaction(list<UTXO>& utxos, Transaction transaction);

	/*
	* searchUTXO
	*
	* Busca y se fija si la utxo existe en lista de utxos
	*
	* utxos: Lista de transacciones salientes
	* utxo: Transaccion particular
	*/
	bool searchUTXO(list<UTXO>& utxos, UTXO utxo);

	/*
	* validateGenesis
	*
	* Valida el bloque genesis
	*
	* block: Genesis block
	*/
	bool validateGenesis(Block block);

	/*
	* genesisBlock
	*
	* Crea un bloque genesis inicial para publicKey.
	*/
	Block genesisBlock(ECDSA<ECP, SHA256>::PublicKey publicKey, double amount);
};