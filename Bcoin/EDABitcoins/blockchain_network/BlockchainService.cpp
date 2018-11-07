#include "BlockchainService.h"

BlockchainService::
BlockchainService(list<UTXO>& _utxos) : utxos(_utxos) {

	/* Nothing to do */
}

BlockchainService::
~BlockchainService(void) {

	/* Nothing to do */
}

double BlockchainService::
fetchBalance(ECDSA<ECP, SHA256>::PublicKey publicKey) {

	double balance = 0;

	/* Recorro las transacciones de salida no gastadas */
	for (UTXO utxo : utxos) {

		/* Busco la que corresponde */
		if (utxo.getOutput().getPublicKey() == publicKey) {

			/* Agrego el monto */
			balance += utxo.getOutput().getAmount();
		}
	}

	return balance;
}

list<UTXO> BlockchainService::
fetchUTXOS(ECDSA<ECP, SHA256>::PublicKey publicKey) {

	list<UTXO> request;

	/* Inicializo */
	request.clear();

	/* Recorro las transacciones de salida no gastadas */
	for (UTXO utxo : utxos) {

		/* Busco la que corresponde */
		if (utxo.getOutput().getPublicKey() == publicKey) {

			/* Agrego el monto */
			request.push_back(utxo);
		}
	}

	return request;

}

bool BlockchainService::
createTransaction(
	ECDSA<ECP, SHA256>::PublicKey from,
	ECDSA<ECP, SHA256>::PublicKey to,
	double amount,
	double minerFee,
	Transaction& newTransaction) {

	/* Inicializo la transaccion */
	newTransaction.clear();

	/* Busco las UTXO del usuario */
	list<UTXO> fromUTXO = fetchUTXOS(from);

	/* Verifico que se pueda pagar */
	if (getAmount(fromUTXO) >= (amount + minerFee)) {

		/* Recupero suficientas salidas no gastadas */
		double inAmount = 0;
		list<UTXO>::iterator itr = fromUTXO.begin();

		while (inAmount < (amount + minerFee)) {

			/* Creo la nueva input */
			Input input;
			input.setOutput(itr->getHashId(), itr->getIndex());

			/* Agrego a la transaccion */
			newTransaction.addInput(input);

			/* Agrego la cantidad parcial */
			inAmount += itr->getOutput().getAmount();

			/* Siguiente */
			itr++;
		}

		/* Agrego las salidas */
		Output output;
		output.setOutput(amount, to);

		newTransaction.addOutput(output);

		/* Si hay sobrante que vuelva */
		if (inAmount > (amount + minerFee)) {
			output.setOutput(inAmount - amount - minerFee, from);

			newTransaction.addOutput(output);
		}
		
		/* Hasheo */
		newTransaction.setTimestamp();
		newTransaction.sign();
		newTransaction.hash();

		/* Todo ok! */
		return true;
	}

	return false;
}

double BlockchainService::
getAmount(list<UTXO>& utxos) {

	double amount = 0;

	for (UTXO utxo : utxos) {

		amount += utxo.getOutput().getAmount();
	}

	return amount;
}

BlockchainMessage BlockchainService::
createTransactionMessage(Transaction transaction) {

	/* Creo el mensaje */
	BlockchainMessage msg(
		BlockchainMessage::Type::NEW_TRANSACTION,
		transaction
	);

	/* Devuelvo */
	return msg;
}

BlockchainMessage BlockchainService::
createTransactionMessage(Transaction transaction, ECDSA<ECP, SHA256>::PrivateKey privateKey) {

	/* Firmamos */
	transaction.sign(privateKey);
	transaction.hash();

	/* Creo el mensaje */
	BlockchainMessage msg = createTransactionMessage(transaction);

	/* Devuelvo */
	return msg;
}

const BlockchainService& BlockchainService::
operator=(const BlockchainService& copy) {

	utxos = copy.utxos;

	return *this;
}