#pragma once

#include "MFsm.h"


class MinerSyncFsm :public MFsm {

public:

	/* Estados de la fsm */
	enum State {
		REQUEST,
		WAIT_BLOCKCHAIN,
		SYNC_OK
	};

	/*
	* Constructor y destructor
	*/
	MinerSyncFsm(Miner& _miner);
	~MinerSyncFsm(void);

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