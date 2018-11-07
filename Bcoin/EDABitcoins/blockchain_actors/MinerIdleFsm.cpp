#include "MinerIdleFsm.h"
#include "Miner.h"

#include "../blockchain_network/BlockchainMessage.h"

MinerIdleFsm::
MinerIdleFsm(Miner& _miner) :MFsm(_miner, State::KEEP_IDLE) {

	/* Reinicio */
	reset();
}

void MinerIdleFsm::
reset(void) {

	/* Estado inicial */
	state = State::KEEP_IDLE;
}

MinerIdleFsm::
~MinerIdleFsm() {

}

void MinerIdleFsm::
runEvent(MinerEvent& event) {
	Block block;
	Transaction transaction;

	/* Segun el estado del idle */
	if ( state == State::KEEP_IDLE ) {

		/* Reviso el evento */
		switch (event.getType()) {

			case MinerEvent::Type::COMMUNICATION:

				/* Segun el tipo de mensaje */
				switch (event.getMessage().getType()) {

					case BlockchainMessage::Type::BLOCKCHAIN_REQUEST:
						/* Respondo el request */
						miner.sendBlockchain();
						break;

					case BlockchainMessage::Type::MINED_BLOCK:
						/* Intento agregar el bloque */
						block = event.getMessage().getBlock();
						if (!miner.addBlock(block)) {
							/* No pude porque esta mal la blockchain, sincronizo */
							state = State::START_SYNC;
						}
						break;

					case BlockchainMessage::Type::NEW_TRANSACTION:
						/* Agrego la transaccion */
						transaction = event.getMessage().getTransaction();
						miner.addCurrTransaction(transaction);
						break;
				}
				break;

			case MinerEvent::Type::PROCESS:

				if (miner.tryStartMining()) {

					state = State::START_MINING;
				}
				break;

		}
	}
}