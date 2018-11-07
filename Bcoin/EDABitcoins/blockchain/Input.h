#pragma once 

#include <sha3.h>
#include <osrng.h>
#include <cryptlib.h>
#include <vector>
#include <eccrypto.h>

using namespace CryptoPP;
using namespace std;

/*
* Input
*
* Esta clase contiene o almacena los datos de una entrada que
* establece la cantidad a transferir durante una transaccion.
* Se construye en torno a una referencia a un UTXO y la firma.
*/
class Input {

public:

	/*
	* Constructores y destructores de Input
	*/
	Input();
	Input(
		string outputHashId,
		unsigned int outputIndex,
		vector<byte> signature
	);
	Input(const Input& copy);
	~Input();

	/*
	* setInput
	* Configura los parametros de la entrada de transaccion
	*
	* outputHashId, outputIndex: Para encontrar la UTXO en registro
	* signature: Firma para autentica el uso de los UTXO
	*/
	void setInput(
		string outputHashId,
		unsigned int outputIndex,
		vector<byte> signature
	);

	bool operator==(const Input& i);

	/* 
	* setOutput
	* Configura los parametros de UTXO de la entrada
	*
	* outputHashId, outputIndex: Elementos para buscar la UTXO
	*/
	void setOutput(string outputHashId, unsigned int outputIndex);

	/* 
	* setSignature
	* Permite firmar la entrada de la transaccion, ya sea con la firma
	* o bien con la private key y calculando internamente
	*/
	void setSignature(vector<byte> signature);
	bool setSignature(ECDSA<ECP, SHA256>::PrivateKey privateKey);

	/*
	* getOutputHash
	* Devuelve el hash id de la transaccion donde esta el UTXO
	*/
	string getOutputHash(void) const;

	/*
	* getOutputIndex
	* Devuelve el indice de la output dentro de las salidas de la
	* transaccion a la cual se refiere para la UTXO
	*/ 
	unsigned int getOutputIndex(void) const;

	/* 
	* getSignature
	* Devuelve la firma de la salida de la transaccion
	*/
	vector<byte> getSignature(void) const;

	/*
	* body
	* Devuelve un string con el cuerpo de la Input
	*/
	string body(void);

	/*
	* unlocks
	* Devuelve true si la public key valida el uso de los inputs firmados
	*
	* publicKey: Clave publica de los UTXO de los que hace uso este input
	*/
	bool unlocks(ECDSA<ECP, SHA256>::PublicKey publicKey);

private:

	string outputHashId;
	unsigned int outputIndex;
	vector<byte> signature;
};