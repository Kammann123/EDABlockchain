#include "BlockchainStorage.h"

#include "../blockchain_algorithm/Verifier.h"

bool BlockchainStorage::
operator==(const BlockchainStorage& cpy) {

	return (cpy.blockchain.size() == blockchain.size()) && (cpy.utxos.size() == utxos.size());
}

BlockchainStorage::
BlockchainStorage(void) {

	/* Valores defecto */
	blockchain.clear();
	utxos.clear();
}

BlockchainStorage::
BlockchainStorage(list<Block>& blockchain, list<UTXO>& utxos) {

	/* Guardo valores */
	this->blockchain = blockchain;
	this->utxos = utxos;
}

BlockchainStorage::
BlockchainStorage(list<Block>& blockchain) {

	/* Guardo valores */
	this->blockchain = blockchain;
}

BlockchainStorage::
BlockchainStorage(const BlockchainStorage& copy) {

	/* Copio valores */
	this->blockchain = copy.blockchain;
	this->utxos = copy.utxos;
}

BlockchainStorage::
~BlockchainStorage(void) {

	/* Nothing to do */
}

bool BlockchainStorage::
addBlock(Block block) {

	/* Valido el bloque */
	if (Verifier::validateBlock(blockchain, utxos, block)) {

		try {

			/* Agrego el bloque */
			blockchain.push_back(block);

			/* Actualizo la utxo */
			updateUTXO(block);

			/* Exito! */
			return true;
		}
		catch (...) {

			return false;
		}
	}

	return false;
}

bool BlockchainStorage::
restaureBlockchain(void) {

	blockchain.clear();
	utxos.clear();
	
	return true;
}

bool BlockchainStorage::
restaureBlockchain(Block block) {

	/* Busco el elemento */
	list<Block>::iterator itr = find(blockchain.begin(), blockchain.end(), block);

	/* Me fijo si existia */
	if (itr != blockchain.end()) {

		/* Creo una version previa */
		blockchain.erase(itr, blockchain.end());

		return true;
	}
	else {

		return false;
	}
}

bool BlockchainStorage::
getBlockchain(list<Block>& blockchain) {

	blockchain = this->blockchain;

	return true;
}

bool BlockchainStorage::
getBlockchain(list<Block>& blockchain, Block& block) {

	/* Busco el elemento */
	list<Block>::iterator itr = find(blockchain.begin(), blockchain.end(), block);

	/* Me fijo si existia */
	if (itr != blockchain.end()) {

		/* Creo una version previa */
		list<Block> newList;

		newList.splice(newList.begin(), blockchain, blockchain.begin(), itr);

		return true;
	}
	else {

		return false;
	}
}

void BlockchainStorage::
updateUTXO(UTXO& utxo) {

	/* Verifico si se agrega o se elimina */
	if (Verifier::searchUTXO(utxos, utxo)) {

		utxos.remove(utxo);
	}
	else {

		utxos.push_back(utxo);
	}
}

void BlockchainStorage::
updateUTXO(string hash, unsigned int index) {

	list<UTXO>::iterator itr = utxos.begin();

	while (itr != utxos.end()) {

		if (itr->getHashId() == hash && itr->getIndex() == index) {

			utxos.erase(itr);
			break;
		}

		itr++;
	}
}

void BlockchainStorage::
updateUTXO(Transaction& transaction) {

	unsigned int index = 0;

	/* Saco las gastadas */
	for (Input input : transaction.getInputs()) {
		updateUTXO(input.getOutputHash(), input.getOutputIndex());
	}

	/* Para cada salida de la transaccion se crean UTXOs */
	for (Output output : transaction.getOutputs()) {

		UTXO newUTXO;

		newUTXO.setReference(transaction.getHash(), index++);
		newUTXO.setOutput(output);

		updateUTXO(newUTXO);
	}
}

void BlockchainStorage::
updateUTXO(Block& block) {

	/* Para cada transaccion del bloque */
	for (Transaction transaction : block.getTransactions()) {

		updateUTXO(transaction);
	}
}

void BlockchainStorage::
updateUTXO(void) {

	/* Limpio la lista */
	utxos.clear();

	/* Revisa y actualiza toda la blockchain */
	for (Block block : blockchain) {

		for (Transaction transaction : block.getTransactions()) {

			unsigned int index = 0;
			for (Output output : transaction.getOutputs()) {

				UTXO newUTXO;

				newUTXO.setReference(transaction.getHash(), index++);
				newUTXO.setOutput(output);

				if (!Verifier::utxoWasSpent(blockchain, newUTXO)) {

					updateUTXO(newUTXO);
				}
			}
		}
	}
}

list<UTXO>& BlockchainStorage::
getUTXO(void) {

	return utxos;
}

bool BlockchainStorage::
oldVersion(string hash, BlockchainStorage& storage) {

	/* Busco ese elemento o bloque */
	list<Block>::iterator itr = blockchain.begin();

	while (itr != blockchain.end()) {

		/* Busco el elemento */
		if (itr->getCurrHash() == hash) {

			/* Creo un nuevo blockchain */
			list<Block> newBlockchain;
			newBlockchain.splice(newBlockchain.begin(), blockchain, blockchain.begin(), ++itr);

			/* Armo el resultado */
			BlockchainStorage result(newBlockchain);
			result.updateUTXO();
			storage = result;

			return true;
		}

		/* Muevo al siguiente */
		itr++;
	}

	/* No encontro version vieja */
	return false;
}