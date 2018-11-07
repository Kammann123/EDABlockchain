#include "Input.h"
#include "cryptoeda.h"

Input::
Input() {

	/* Nothing  to do */
}

Input::
Input(string outputHashId, unsigned int outputIndex, vector<byte> signature) {

	/* Configuro los parametros */
	this->setInput(outputHashId, outputIndex, signature);
}

Input::
Input(const Input& copy) {

	/* Configuro parametros */
	this->setInput(copy.getOutputHash(), copy.getOutputIndex(), copy.getSignature());
}

Input::
~Input() {

	/* Nothing to do */
}

void Input::
setInput(string outputHashId, unsigned int outputIndex, vector<byte> signature) {

	/* Configuro los parametros */
	this->setOutput(outputHashId, outputIndex);
	this->setSignature(signature);
}

void Input::
setOutput(string outputHashId, unsigned int outputIndex) {

	/* Configuro datos de la salida referida */
	this->outputHashId = outputHashId;
	this->outputIndex = outputIndex;
}

void Input::
setSignature(vector<byte> signature) {

	/* Configuro parametro */
	this->signature = signature;
}

bool Input::
setSignature(ECDSA<ECP, SHA256>::PrivateKey privateKey) {

	bool good;
	string data = this->outputHashId + to_string(this->outputIndex);

	/* Obtengo la firma correspondiente */
	this->signature = cryptoeda::generateSignature(
		privateKey,
		data,
		good
	);

	/* Devuelvo si fue exitoso o no! */
	return good;
}

string Input::
getOutputHash(void) const {

	return this->outputHashId;
}

unsigned int Input::
getOutputIndex(void) const {

	return this->outputIndex;
}

vector<byte> Input::
getSignature(void) const {

	return this->signature;
}

string Input::
body(void) {

	string body = this->outputHashId
		+ to_string(this->outputIndex)
		+ cryptoeda::getStringFromBytes(this->signature);

	return body;
}

bool Input::
unlocks(ECDSA<ECP, SHA256>::PublicKey publicKey) {

	string body = this->outputHashId + to_string(this->outputIndex);

	/* Verifico si fue o no desbloqueada */
	return cryptoeda::verifySignature(publicKey, body, signature);
}

bool Input::
operator==(const Input& i) {

	return (outputHashId == i.outputHashId) && (outputIndex == i.outputIndex) && (signature == i.signature);
}