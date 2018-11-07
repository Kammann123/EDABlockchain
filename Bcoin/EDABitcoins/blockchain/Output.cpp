#include "Output.h"
#include "cryptoeda.h"
#include <osrng.h>

Output::Output() {

	/* Valores default */
	amount = 0;
}

Output::
Output(double amount, ECDSA<ECP, SHA256>::PublicKey publicKey) {

	/* Configuro parametros */
	this->setOutput(amount, publicKey);
}

Output::
Output(const Output& copy) {

	/* Copio los valores o parametro s*/
	this->setOutput(copy.amount, copy.getPublicKey());
}

Output::
~Output() {

	/* Nothing to free */
}

void Output::
setOutput(double amount, ECDSA<ECP, SHA256>::PublicKey publicKey) {

	/* Configuro */
	this->amount = amount;
	this->publicKey = publicKey;
}

double Output::
getAmount(void) {

	/* Devuelvo la cantidad */
	return this->amount;
}

ECDSA<ECP, SHA256>::PublicKey Output::
getPublicKey(void) const{

	/* Devuelvo el public key */
	return this->publicKey;
}

string Output::
body(void) {

	vector<byte> pubKey = cryptoeda::getByteArray(publicKey);

	string body = to_string(amount) +
		cryptoeda::getStringFromBytes(pubKey);

	return body;
}

bool Output::
operator==(const Output& output) {

	bool good;

	good = (amount == output.amount)
		&& (publicKey == output.publicKey);

	return good;
}