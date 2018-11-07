#pragma once

#include "MinerEvent.h"

class Miner;

/*
* Maquina de estados del mineroW
*/
class MFsm {

public:

	/*
	* Constructores y destructores
	*/
	MFsm(Miner& _miner, unsigned int status);
	~MFsm();

	const MFsm& operator=(const MFsm& copy);

	/*
	* getStatus
	*
	* Devuelve el estado actual de la fsm
	*/
	unsigned int getStatus(void);

	/*
	* reset
	*
	* Reinicia la fsm a su estado inicial
	*/
	virtual void reset(void) = 0;

	/*
	* runEvent
	*
	* Ejecuta y procesa un evento
	*/
	virtual void runEvent(MinerEvent& event) = 0;

protected:

	unsigned int state;
	Miner& miner;
};