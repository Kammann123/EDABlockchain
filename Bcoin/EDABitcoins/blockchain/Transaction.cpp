#include "Transaction.h"
#include "cryptoeda.h"

Transaction::
Transaction(void) {

	/* Valores default */
	hashID = "";
	timestamp = 0;
}

Transaction::
Transaction(const Transaction& copy) {

	/* Guardo y copio valores */
	hashID = copy.hashID;
	inputs = copy.inputs;
	outputs = copy.outputs;
	timestamp = copy.timestamp;
}

Transaction::
~Transaction() {

	/* Nothing to do */
}

bool Transaction::
operator==(const Transaction& op) {
	bool found;

	/* Comparo cantidad de inputs */
	if (inputs.size() == op.inputs.size()) {

		/* Me fijo que sean iguales */
		for (Input input : inputs) {

			found = false;
			for (Input opinput : op.inputs) {

				if (input == opinput) {
					found = true;
					break;
				}
			}

			if (!found) {
				return false;
			}
		}

		/* Paso, entonces ok! */
		return true;
	}

	return false;
}

void Transaction::
clear(void) {

	/* Valores por defecto */
	hashID = "";

	/* Limpio las listas */
	inputs.clear();
	outputs.clear();
}

bool Transaction::
addInput(const Input& input) {

	try {
		inputs.push_back(input);

		return true;
	}
	catch (...) {

		return false;
	}
}

bool Transaction::
addOutput(const Output& output) {

	try {
		outputs.push_back(output);

		return true;
	}
	catch (...) {

		return false;
	}
}

string Transaction::
body(void) {

	string body = hashID + dataBody();

	return body;
}

void Transaction::
hash(void) {

	string body = dataBody();

	/* Hago el hash */
	this->hashID = cryptoeda::hash(body);
}

string Transaction::
dataBody(void) const {

	/* Recupero el body */
	string body = to_string(timestamp);

	/* Agrego todas las inputs */
	for (Input input : inputs) {

		body += input.body();
	}

	/* Agrego cantidad de inputs */
	body += to_string(inputs.size());

	/* Agrego todas las outputs */
	for (Output output : outputs) {

		body += output.body();
	}

	/* Agrego la cantidad de outputs */
	body += to_string(outputs.size());

	return body;
}

string Transaction::
getHash(void) const {

	return this->hashID;
}

list<Input> Transaction::
getInputs(void) const {

	return this->inputs;
}

list<Output> Transaction::
getOutputs(void) const {

	return this->outputs;
}

bool Transaction::
validateHash(void){

	/* Obtengo el cuerpo de la transaccion */
	string body = dataBody();

	/* Calculo el hash */
	string hash = cryptoeda::hash(body);

	/* Verifico */
	return (hash == this->hashID);
}

void Transaction::
sign(ECDSA<ECP, SHA256>::PrivateKey privateKey) {

	for (Input& input : inputs) {

		input.setSignature(privateKey);
	}
}

void Transaction::
sign(void) {

	for (Input& input : inputs) {

		input.setSignature({0});
	}
}

void Transaction::
setTimestamp(void) {

	this->timestamp = (int)time(NULL);
}

int Transaction::
getTimestamp(void) {

	return timestamp;
}