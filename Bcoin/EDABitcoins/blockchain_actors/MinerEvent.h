#pragma once

#include "../blockchain_network/BlockchainMessage.h"

/*
* MinerEvent
*
* Los eventos que se le comunican a la FSM del minero
*/
class MinerEvent {

public:

	/*
	* Tipos de los eventos
	*/
	enum class Type : unsigned int {
		COMMUNICATION,
		PROCESS
	};

	/*
	* Constructor y destructor
	*/
	MinerEvent(Type type);
	MinerEvent(Type type, BlockchainMessage msg);
	~MinerEvent(void);

	/*
	* Getters y setters
	*/
	void setMessage(BlockchainMessage& msg);
	void setType(Type& type);
	Type getType(void);
	BlockchainMessage getMessage(void);

private:
	Type type;
	BlockchainMessage msg;
};