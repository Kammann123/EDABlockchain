#pragma once

/* Valores iniciales de la blockchain */
#define DEFAULT_CHALLENGE		10//25
#define DEFAULT_FEE				50
#define DEFAULT_SATOSHI			0.00000001

#define MAX_NMBR_OF_CEROS_ON_HASH	10
#define RUNS_PER_CERO				5

#include <string>

using namespace std;

/*
* BlockchainContext
*
* Esta clase de tipo estatica esta dedicada a definir el contexto en que funciona
* la simulacion del proceso de la blockchain, para almacenar las variables de interes
* como lo son los parametros del POW, es decir el nounce, o bien el consenso sobre las
* tasas.
*/
class BlockchainContext {

public:

	/*
	* getChallenge
	*
	* Devuelve la cantidad de 0 que deben ser colocados en el nounce
	*/
	static unsigned int getChallenge(void);

	/*
	* getMinerFee
	* 
	* Devuelve la cantidad de monedas virtuales por minar un bloque
	*/
	static double getMinerFee(void);

	/*
	* generateChallenge
	* 
	* Genera un nuevo valor de challenge en funcion del tiempo medio para 
	* realizar la operacion de minado
	*/
	static void generateChallenge(void);
	
	/*
	* generateFee
	*
	* Genera un nuevo valor de tasa para pagar por el minado
	*/
	static void generateFee(void);

	/*
	* getSatoshi
	*
	* Devuelve la cantidad de satoshis
	*/
	static double getSatoshi(void);

	/*
	* validatePOW
	*
	* Valida prueba de trabajo, verifica que sea valido el hash
	*
	* hash: Hash a verificar
	*/
	static bool validatePOW(string hash);

private:

	/* Bloqueo la creacion de un objeto */
	BlockchainContext();

	static unsigned int challenge;
	static double minerFee;
	static double satoshi;
};