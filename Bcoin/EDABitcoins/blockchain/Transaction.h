#pragma once

#include <string>
#include <list>
#include "Input.h"
#include "Output.h"

using namespace std;

/*
* Transaction
* 
* Esta clase es una transaccion dentro de la red EDACoin
* y contiene los datos que la constituyen y los metodos para 
* manejarla adecuadamente.
*
* Se construyen transactions con entradas y salidas (Input, Output)
*/
class Transaction {

public:

	/*
	* Constructores y destructores de la la Transaction
	*/
	Transaction(void);
	Transaction(const Transaction& copy);
	~Transaction(void);

	/*
	* Operadores sobrecargados
	*/
	bool operator==(const Transaction& op);

	/*
	* clear
	* Limpia y borra el contenido de la transaction
	*/
	void clear(void);

	/*
	* setTimestamp
	*/
	void setTimestamp(void);
	int getTimestamp(void);

	/*
	* addInput
	* Agrega una nueva entrada a la transaction
	*
	* input: Entrada
	*/
	bool addInput(const Input& input);

	/*
	* addOutput
	* Agrega una nueva salida a la transaction
	*
	* output: Salida
	*/
	bool addOutput(const Output& output);

	/* 
	* body
	* Devuelve un string con el cuerpo de la transaction
	*/
	string body(void);

	/*
	* hash
	* Hashea el contenido actual de la transaction
	*/
	void hash(void);

	/*
	* getHash
	* Devuelve el hashId de la transaction
	*/
	string getHash(void) const;

	/*
	* getInputs
	* Devuelve la lista de entradas de la transaction
	*/
	list<Input> getInputs(void) const;

	/*
	* getOutputs
	* Devuelve la lista de salidas de la transaction
	*/
	list<Output> getOutputs(void) const;

	/*
	* validateHash
	* Valida el contenido y verifica que contraste el hashId
	*/
	bool validateHash(void);

	/*
	* sign
	*
	* Permite firmar todas las transacciones
	*/
	void sign(ECDSA<ECP, SHA256>::PrivateKey privateKey);
	void sign(void);

private:

	/*
	* dataBody
	* String del cuerpo sin el hashID
	*/
	string dataBody(void) const;

	int timestamp;
	string hashID;
	list<Input> inputs;
	list<Output> outputs;
};