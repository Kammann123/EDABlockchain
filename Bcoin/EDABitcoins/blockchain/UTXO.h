#pragma once

#include <string>

#include "Output.h"

using namespace std;

/*
* UTXO
* 
* La clase UTXO modela un objeto de transaccion saliente no gastada
* para almacenar en una lista tanto la salida de una transaccion como los datos
* de la transaccion para ubicarla dentro del blockchain.
*/
class UTXO {

public:

	/*
	* Constructores y destructores de UTXO
	*/
	UTXO(string hashID, unsigned int index, Output output);
	UTXO();
	UTXO(const UTXO& copy);
	~UTXO();

	/*
	* Sobrecarga de operadores
	*/
	bool operator==(const UTXO& utxo);

	/*
	* setReference
	* Configura la referencia a la transaccion de salida dentro del blockchain.
	*
	* hashID: hash de la transaccion
	* index: Indice de output dentro de transaccion
	*/
	void setReference(string hashID, unsigned int index);

	/*
	* setOutput
	* Configura el dato de la salida dentro de la transaccion que hace a la UTXO
	*
	* output: Salida de transaccion
	*/
	void setOutput(Output output);

	/*
	* Getters de la UTXO
	*/
	string getHashId(void) const;
	unsigned int getIndex(void) const;
	Output getOutput(void) const;

private:

	string hashID;
	unsigned int index;
	Output output;
};