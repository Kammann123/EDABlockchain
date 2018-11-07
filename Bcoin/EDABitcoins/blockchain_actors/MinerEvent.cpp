#include "MinerEvent.h"

MinerEvent::Type MinerEvent::
getType(void) {

	return type;
}

BlockchainMessage MinerEvent::
getMessage(void) {

	return msg;
}

void MinerEvent::
setMessage(BlockchainMessage& msg) {

	this->msg = msg;
}

void MinerEvent::
setType(Type& type) {

	this->type = type;
}

MinerEvent::
MinerEvent(Type type) {

	setType(type);
}

MinerEvent::
MinerEvent(Type type, BlockchainMessage msg) {
	
	setType(type);
	setMessage(msg);
}

MinerEvent::
~MinerEvent(void) {

	/* Nothing to do */
}