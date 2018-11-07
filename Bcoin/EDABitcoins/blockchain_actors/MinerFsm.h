#pragma once

#include "MinerIdleFsm.h"
#include "MinerSyncFsm.h"
#include "MinerMiningFsm.h"

class MinerFsm : public MFsm {

public:

	/* Estados de la fsm */
	enum State {
		IDLE,
		MINING,
		SYNC
	};

	/*
	* Constructor y destructor
	*/
	MinerFsm(Miner& _miner);
	~MinerFsm(void);
	
	const MinerFsm& operator=(const MinerFsm& copy);

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

private:

	MinerIdleFsm idleFsm;
	MinerSyncFsm syncFsm;
	MinerMiningFsm miningFsm;
};