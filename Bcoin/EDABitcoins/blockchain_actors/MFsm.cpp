#include "MFsm.h"
#include "Miner.h"

MFsm::
MFsm(Miner& _miner, unsigned int status) : miner(_miner) {

	/* Estado inicial */
	this->state = state;
}

MFsm::
~MFsm(){


}

unsigned int MFsm::
getStatus(void) {

	return state;
}

const MFsm& MFsm::
operator=(const MFsm& copy) {
	state = copy.state;
	miner = copy.miner;

	return *this;
}