#pragma once

#include "MFsm.h"

class MinerIdleFsm : public MFsm {

public:

	/* Estados de la fsm */
	enum State {
		KEEP_IDLE,
		START_SYNC,
		START_MINING
	};

	/* 
	* Constructor y destructor 
	*/
	MinerIdleFsm(Miner& _miner);
	~MinerIdleFsm(void);

	/*
	* reset
	*
	* Reinicia la fsm a su estado inicial
	*/
	virtual void reset(void);

	/*
	* runEvent
	*
	* Ejecuta y procesa un evento
	*/
	virtual void runEvent(MinerEvent& event);
};