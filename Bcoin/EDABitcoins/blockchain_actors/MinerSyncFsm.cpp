#include "MinerSyncFsm.h"
#include "Miner.h"

MinerSyncFsm::
MinerSyncFsm(Miner& _miner) :MFsm(_miner, State::REQUEST) {

	/* Reset */
	reset();
}

MinerSyncFsm::
~MinerSyncFsm() {


}

void MinerSyncFsm::
reset(void) {

	/* Reset */
	state = State::REQUEST;
}

void MinerSyncFsm::
runEvent(MinerEvent& event) {
	Transaction transaction;
	BlockchainStorage blockchain;

	/* Segun el estado */
	switch (state) {

		case State::REQUEST:
			if (event.getType() == MinerEvent::Type::COMMUNICATION) {

				/* Si el mensaje es una nueva transaccion la guardo para no perdermela */
				if (event.getMessage().getType() == BlockchainMessage::Type::NEW_TRANSACTION) {

					transaction = event.getMessage().getTransaction();
					miner.addCurrTransaction(transaction);
				}
			}
			else {

				/* Envio la peticion */
				miner.sendBlockchainRequest();

				/* Cambio a espera */
				state = State::WAIT_BLOCKCHAIN;
			}
			break;

		case State::WAIT_BLOCKCHAIN:

			if (event.getType() == MinerEvent::Type::COMMUNICATION) {

				/* Si recibo la blockchain */
				if (event.getMessage().getType() == BlockchainMessage::Type::BLOCKCHAIN) {

					blockchain = event.getMessage().getBlockchain();

					/* Sincronizo con la blockchain dada */
					miner.syncBlockchain(blockchain);

					/* Termine */
					state = State::SYNC_OK;
				}
			}
			break;
	}
}