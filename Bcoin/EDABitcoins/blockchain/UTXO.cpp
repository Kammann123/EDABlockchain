#include "UTXO.h"

UTXO::
UTXO() {

	/* Valores por defecto */
	hashID = "";
	index = 0;
}

UTXO::
UTXO(string hashID, unsigned int index, Output output) {

	/* Configuro parametros */
	this->hashID = hashID;
	this->index = index;
	this->output = output;
}

UTXO::
UTXO(const UTXO& copy) {

	/* Copio los parametros */
	this->hashID = copy.hashID;
	this->index = copy.index;
	this->output = copy.output;
}

UTXO::
~UTXO() {

	/* Nothing to do */
}

void UTXO::
setReference(string hashID, unsigned int index) {

	this->hashID = hashID;
	this->index = index;
}

void UTXO::
setOutput(Output output) {

	this->output = output;
}

string UTXO::
getHashId(void) const {

	return hashID;
}

unsigned int UTXO::
getIndex(void) const {

	return index;
}

Output UTXO::
getOutput(void) const {

	return output;
}

bool UTXO::
operator==(const UTXO& utxo) {

	bool good;

	good = (hashID == utxo.hashID)
		&& (index == utxo.index)
		&& (output == utxo.output);

	return good;
}