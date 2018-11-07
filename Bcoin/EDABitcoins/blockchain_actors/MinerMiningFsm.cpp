#include "MinerMiningFsm.h"
#include "Miner.h"

#include "../blockchain_network/BlockchainContext.h"

MinerMiningFsm::
MinerMiningFsm(Miner& _miner) : MFsm(_miner, State::PREPARE) {

	/* Reset */
	reset();
}

MinerMiningFsm::
~MinerMiningFsm(void) {

}

void MinerMiningFsm::
reset(void) {

	state = State::PREPARE;
	block.clear();
	nonceTries.clear();
}

void MinerMiningFsm::
manageMinedBlock(Block& block) {
	bool continueMining;

	/* Termino el minado */
	if (!miner.addBlock(block, continueMining)) {

		state = State::SYNC;
	}
	else {

		if (!continueMining) {

			state = State::TERMINATE;
		}
	}
}

void MinerMiningFsm::
runEvent(MinerEvent& event) {
	Transaction transaction;
	Block block;

	/* Segun el evento */
	switch (state) {

		case State::PREPARE:

			if (event.getType() == MinerEvent::Type::COMMUNICATION) {

				/* Segun el mensaje */
				switch (event.getMessage().getType()) {

					case BlockchainMessage::Type::NEW_TRANSACTION:
						transaction = event.getMessage().getTransaction();

						/* Agrego nueva transaccion */
						miner.addNextTransaction(transaction);
						break;

					case BlockchainMessage::Type::MINED_BLOCK:
						block = event.getMessage().getBlock();
						manageMinedBlock(block);
						break;
				}
			}
			else {

				/* Tengo que procesar la preparacion del bloque */
				this->block = miner.prepareCurrBlock();

				/* Cambio a nuevo estado */
				state = State::NONCE;
			}
			break;
		
		case State::NONCE:

			if (event.getType() == MinerEvent::Type::COMMUNICATION) {

				switch (event.getMessage().getType()) {

					case BlockchainMessage::Type::NEW_TRANSACTION:
						transaction = event.getMessage().getTransaction();

						/* Agrego nueva transaccion */
						miner.addNextTransaction(transaction);
						break;

					case BlockchainMessage::Type::MINED_BLOCK:
						block = event.getMessage().getBlock();
						manageMinedBlock(block);
						break;
				}
			}
			else {

				/* Pruebo con el nonce siguiente! */
				if (tryNewNonce()) {

					state = State::SEND;
				}
			}
			break;

		case State::SEND:

			if (event.getType() == MinerEvent::Type::COMMUNICATION) {

				switch (event.getMessage().getType()) {

				case BlockchainMessage::Type::NEW_TRANSACTION:
					transaction = event.getMessage().getTransaction();

					/* Agrego nueva transaccion */
					miner.addNextTransaction(transaction);
					break;

				case BlockchainMessage::Type::MINED_BLOCK:
					block = event.getMessage().getBlock();
					manageMinedBlock(block);
					break;
				}
			}
			else {

				/* Mando el bloque */
				miner.sendBlock(this->block);

				state = State::DONE;
			}
			break;
	}
}

bool MinerMiningFsm::
tryNewNonce(void) {
	unsigned int nonce;

	/* Busco aleatorios que no esten ya usado */
	do {

		/* Nuevo numero */
		nonce = rand() * rand();
	} while (find(nonceTries.begin(), nonceTries.end(), nonce) != nonceTries.end());

	/* Agrego a la lista */
	nonceTries.push_back(nonce);

	/* Con el valor actual de nonce pruebo */
	block.setNonce(nonce);
	block.hash();

	/* Obtengo el hash y valido POW */
	string hash = block.getCurrHash();

	/* Resultado */
	return BlockchainContext::validatePOW(hash);
}