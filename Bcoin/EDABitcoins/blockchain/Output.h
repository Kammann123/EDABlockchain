#pragma once

#include <eccrypto.h>
#include <cryptlib.h>
#include <sha3.h>

using namespace CryptoPP;
using namespace std;

/* 
* Output
*
* Esta clase representa una salida o destino de una cantidad de monedas
* dentro de una transaccion en la blockchain y se construye con la cantidad
* y el destinatario.
*/
class Output {

public:

	/* 
	* Constructores y destructores de Output
	*/
	Output();
	Output(double amount, ECDSA<ECP, SHA256>::PublicKey publicKey);
	Output(const Output& copy);
	~Output();
	
	/*
	* Sobrecargada de operadores
	*/
	bool operator==(const Output& output);

	/*
	* setOutput
	* Establece los valores de Output
	*
	* amount, publicKey: datos del output
	*/
	void setOutput(double amount, ECDSA<ECP, SHA256>::PublicKey publicKey);

	/* 
	* getAmount
	* Devuelve la cantidad definida en el output
	*/
	double getAmount(void);

	/*
	* getPublicKey
	* Devuelve la clave public del destinatario quien
	* recibe el monto de la transaccion de salida
	*/
	ECDSA<ECP, SHA256>::PublicKey getPublicKey(void) const;

	/* 
	* body
	* Devuelve un string con el cuerpo del output
	*/
	string body(void);

private:

	double amount;
	ECDSA<ECP, SHA256>::PublicKey publicKey;
};