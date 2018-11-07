#pragma once

#include "FullService.h"
#include "../FullServiceView.h"
#include "../FullServiceController.h"
#include "Miner.h"
#include "../Graphics.h"


/*
* ActorFactory
*
* Fabrica de actores para el blockchain
*/
class ActorFactory {
	
public:
	/*
	* create
	*
	* Crea un blockchain node segun el tipo que se le pide
	*/
	static FullServiceController* create(unsigned int type, Graphics& graphics);
	static FullServiceController* create(unsigned int type, Graphics& graphics, ECDSA<ECP, SHA256>::PrivateKey pKey);
	static void destroy(FullServiceController* controller);
};