#include "MinerFsm.h"

MinerFsm::
MinerFsm(Miner& _miner) : MFsm(_miner, State::IDLE), idleFsm(_miner), syncFsm(_miner), miningFsm(_miner){

	/* Reset */
	reset();
}

MinerFsm::
~MinerFsm() {

}

void MinerFsm::
reset(void) {

	/* Estado inicial */
	state = State::IDLE;
	idleFsm.reset();
	syncFsm.reset();
	miningFsm.reset();
}

void MinerFsm::
runEvent(MinerEvent& event) {

	switch (state) {

		case State::IDLE:
			/* Corro la fsm  */
			idleFsm.runEvent(event);

			/* Verifico estado */
			if (idleFsm.getStatus() == MinerIdleFsm::State::START_MINING) {
				state = State::MINING;
				miningFsm.reset();
			}
			else if (idleFsm.getStatus() == MinerIdleFsm::State::START_SYNC) {
				state = State::SYNC;
				syncFsm.reset();
			}
			break;

		case State::MINING:
			/* Corro la fsm */
			miningFsm.runEvent(event);

			/* Verifico estados */
			switch (miningFsm.getStatus()) {

				case MinerMiningFsm::State::SYNC:

					state = State::SYNC;
					syncFsm.reset();
					break;

				case MinerMiningFsm::State::DONE: case MinerMiningFsm::State::TERMINATE:

					state = State::IDLE;
					idleFsm.reset();
					break;
			}
			break;

		case State::SYNC:
			/* Corro la fsm */
			syncFsm.runEvent(event);

			/* Verifico estados */
			if (syncFsm.getStatus() == MinerSyncFsm::State::SYNC_OK) {

				state = State::IDLE;
				idleFsm.reset();
			}
			break;

	}
}

const MinerFsm& MinerFsm::
operator=(const MinerFsm& copy) {

	idleFsm = copy.idleFsm;
	syncFsm = copy.syncFsm;
	miningFsm = copy.miningFsm;

	return *this;
}