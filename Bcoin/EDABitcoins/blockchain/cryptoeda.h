#pragma once

#include "cryptlib.h"
#include "osrng.h"
#include "eccrypto.h"
#include "oids.h"
#include "hex.h"
#include "sha3.h"
#include <string>

using namespace std;
using namespace CryptoPP;

/*
* cryptoeda
* La idea de la biblioteca cryptoeda es tener un conjunto de funciones
* que son da amplia utilidad para trabajar con hashing, ecdsa y procesos
* de encriptacion/desencriptacion para criptomonedas y luego facilitar
* el trabajo.
*/
namespace cryptoeda {

	#define PRIVATE_KEY_CHARS 20
	#define PUBLIC_KEY_CHARS 40

	/*
	* generatePrivateKey
	*
	* Genera una clave privada con hash sha256 para el manejo de
	* la encriptacion de datos dentro de la blockchain
	*
	* good: Devuelve si la operacion fue exitosa!
	*/
	ECDSA<ECP, SHA256>::PrivateKey generatePrivateKey(bool& good);

	/*
	* generateSignature
	*
	* Genera una firma segura con la private key dada sobre los datos
	* que se pasan como string por data
	*
	* privateKey: Clave privada del usuario o cliente
	* data: Informacion en forma de string a firmar
	* good: Devuelve si la operacion fue exitosa!
	*/
	vector<byte> generateSignature(ECDSA<ECP, SHA256>::PrivateKey& privateKey, string& data, bool& good);

	/*
	* verifySignature
	*
	* Verifica que la firma de los datos dados sea valida contra la
	* clave publica del usuario o cliente dueño
	*
	* publicKey: Clave publica del usuario
	* data: Datos firmados y locked
	* signature: Firma de los datos
	*/
	bool verifySignature(ECDSA<ECP, SHA256>::PublicKey& publicKey, string& data, vector<byte>& signature);

	/*
	* hash
	* 
	* Aplica el hash SHA256 al conjunto de datos almacenados en el string
	*
	* data: Datos a hashear
	*/
	string hash(string& data);

	/* 
	* getStringFromBytes
	*
	* Devuelve un string conformado por los bytes del arreglo de bytes
	*
	* byteArray: Arreglo de bytes
	*/
	string getStringFromBytes(vector<byte>& byteArray);

	/*
	* getByteArray
	* 
	* Devuelve un arreglo de bytes con los datos de la clave ya sea
	* publica o privada segun que version de la funcion se emplee.
	*
	* publicKey/privateKey: Claves
	*/
	vector<byte> getByteArray(ECDSA<ECP, SHA256>::PublicKey publicKey);
	vector<byte> getByteArray(ECDSA<ECP, SHA256>::PrivateKey privateKey);
};