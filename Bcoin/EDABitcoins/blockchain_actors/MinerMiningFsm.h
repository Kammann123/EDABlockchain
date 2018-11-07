#pragma once

#include "MFsm.h"

#include <list>

using namespace std;

class MinerMiningFsm : public MFsm {

public:

	/* Estados de la fsm */
	enum State {
		PREPARE,
		NONCE,
		SEND,
		TERMINATE,
		SYNC,
		DONE
	};

	/*
	* Constructor y destructor
	*/
	MinerMiningFsm(Miner& _miner);
	~MinerMiningFsm(void);

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

	/*
	* tryNewNonce
	* 
	* Prueba el bloque con un nuevo nonce
	*/
	bool tryNewNonce(void);

	/*
	* manageMinedBlock
	*
	* Administro los bloques minados recibidos
	*/
	void manageMinedBlock(Block& block);

	list<unsigned int> nonceTries;
	Block block;
};