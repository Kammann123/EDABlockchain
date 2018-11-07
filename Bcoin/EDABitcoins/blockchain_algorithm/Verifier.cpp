#include "Verifier.h"
#include "../blockchain_network/BlockchainContext.h"

#include <cstdlib>

bool Verifier::
utxoWasSpent(list<Block>& blockchain, UTXO utxo) {

	for (Block block : blockchain) {

		for (Transaction transaction : block.getTransactions()) {

			for (Input input : transaction.getInputs()) {

				if (utxo.getHashId() == input.getOutputHash()
					&& utxo.getIndex() == input.getOutputIndex()) {

					return true;
				}
			}
		}
	}

	return false;
}

bool Verifier::
searchUTXO(list<UTXO>& utxos, UTXO utxo) {

	list<UTXO>::iterator itr = find(utxos.begin(), utxos.end(), utxo);

	return itr != utxos.end();
}

bool Verifier::
searchTransaction(list<UTXO>& utxos, Transaction transaction) {

	/* Busco por cada UTXO */
	for (UTXO utxo : utxos) {

		/* Verifico por hash */
		if (utxo.getHashId() == transaction.getHash()) {

			return true;
		}
	}

	return false;
}

bool Verifier::
searchOutput(list<UTXO>& utxos, string hashID, unsigned int index, Output& output) {

	/* Busco entre las utxo */
	for (UTXO utxo : utxos) {

		/* Busco la del hash de transaccion correspondiente */
		if (utxo.getHashId() == hashID && utxo.getIndex() == index) {
		
			output = utxo.getOutput();
			return true;
		}
	}

	return false;
}

double Verifier::
getMinerTip(list<UTXO>& utxos, Transaction& transaction) {

	double tip = 0;

	/* Busco los valores de salida */
	for (Output output : transaction.getOutputs()) {

		/* Busco los valores */
		tip -= output.getAmount();
	}

	Output out;

	/* Busco los valores de entrada */
	for (Input input : transaction.getInputs()) {

		/* Busco la salida que refiere la input */
		if (searchOutput(utxos, input.getOutputHash(), input.getOutputIndex(), out)) {

			/* Agrego el valor */
			tip += out.getAmount();
		}
	}

	return tip;
}

bool Verifier::
validateTransaction(list<UTXO>& utxos, Transaction& transaction) {

	/* Valido el hash de la transaccion */
	if (!transaction.validateHash()) {

		return false;
	}

	/* Valido que las referencias en inputs sean no gastadas */
	for (Input input : transaction.getInputs()) {

		Output out;

		/* Valido que las encuentre */
		if (searchOutput(utxos, input.getOutputHash(), input.getOutputIndex(), out)) {

			/* Al encontrarlas verifico que las pueda usar */
			if (!input.unlocks(out.getPublicKey())) {

				return false;
			}
		}
		else {

			return false;
		}
	}

	/* Verifico los montos de output y input */
	double tip = getMinerTip(utxos, transaction);
	if (tip < 0) {

		return false;
	}

	/* Validacion correcta */
	return true;
}

bool Verifier::
validateGenesis(Block block) {

	string hash = block.getPrevHash();
	unsigned int i = 0;

	/* Lo unico que veo es que el hash previo sea 32 0s */
	for (unsigned char c : hash) {

		if (c == '0') {
			i++;
		}
		else {
			return false;
		}
	}

	/* Valido */
	if (i == 32) {

		return true;
	}
	else {

		return false;
	}
}

bool Verifier::
validateBlock(list<Block>& blockchain, list<UTXO>& utxos, Block& block) {

	/* Valido que el hash del bloque sea correcto */
	if (!block.validateHash()) {

		return false;
	}
	
	if (blockchain.empty()) {

		/* Valido el genesis */
		if (validateGenesis(block)) {

			return true;
		}
		else {

			return false;
		}
	}
	else {

		/* Verifico que el hash de bloque previo sea el correcto */
		if (block.getPrevHash() != blockchain.back().getCurrHash()) {

			return false;
		}

		/* Valido que cumpla el challenge */
		if (!BlockchainContext::validatePOW(block.getCurrHash())) {

			return false;
		}

		unsigned int i = 0;
		/* Verifico que todas las transacciones sean validas */
		for (Transaction transaction : block.getTransactions()) {

			/* La del minero */
			if (i == 0) {
				/* Valido ninguna input */
				if (!transaction.getInputs().empty()) {
					return false;
				}

				/* Valido una salida */
				if (transaction.getOutputs().size() != 1) {
					return false;
				}

				/* Valido cantidad de salida */
				if (transaction.getOutputs().front().getAmount() != BlockchainContext::getMinerFee()) {

					return false;
				}
			}
			else {
				/* Verifico cada una */
				if (validateTransaction(utxos, transaction)) {

					/* Verifico la suma nula */
					if (abs(getMinerTip(utxos, transaction)) > BlockchainContext::getSatoshi()) {

						return false;
					}
				}
				else {

					return false;
				}
			}

			i++;
		}
	}
	

	/* Exito! */
	return true;
}

Block Verifier::
genesisBlock(ECDSA<ECP, SHA256>::PublicKey publicKey, double amount) {

	Block block;
	string genesisHash;
	Output output;
	Transaction transaction;

	/* Genesis hash */
	for (unsigned int i = 0; i < 32; i++)
		genesisHash += "0";

	/* Hash genesis previo al bloque */
	block.setPrevBlock(genesisHash);

	/* Timestamp */
	block.setTimestamp();

	/* Set nonce */
	block.setNonce(0);

	/* Salida transaccion */
	output.setOutput(amount, publicKey);
	transaction.addOutput(output);
	transaction.hash();
	block.addTransaction(transaction);

	/* Hash */
	block.hash();

	return block;
}