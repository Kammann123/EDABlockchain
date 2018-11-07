#pragma once

#include "BlockchainNode.h"

BlockchainNode::
BlockchainNode() {

	bool good;

	/* Genero una private key aleatoria */
	privateKey = cryptoeda::generatePrivateKey(good);

	/* Genero una public key */
	privateKey.MakePublicKey(publicKey);
}

BlockchainNode::
BlockchainNode(ECDSA<ECP, SHA256>::PrivateKey privateKey) {

	/* Guardo la key privada */
	this->privateKey = privateKey;

	/* Guardo la publica */
	this->privateKey.MakePublicKey(publicKey);
}

BlockchainNode::
~BlockchainNode() {

	/* Nothing to do */
}

bool BlockchainNode::
operator==(const BlockchainNode& node) {

	return publicKey == node.publicKey;
}

bool BlockchainNode::
operator!=(const BlockchainNode& node) {

	return !(*this == node);
}

const BlockchainNode& BlockchainNode::
operator=(const BlockchainNode& node) {

	this->publicKey = node.publicKey;
	this->privateKey = node.privateKey;
	this->msgQueue = node.msgQueue;
	this->msgBuffer = node.msgBuffer;
	this->connectionNodes = node.connectionNodes;

	return *this;
}

bool BlockchainNode::
isConnectedTo(BlockchainNode& node) {

	list<BlockchainNode*>::iterator itr;

	/* Busco el elemento */
	itr = find(connectionNodes.begin(), connectionNodes.end(), &node);

	/* Devuelvo resultado */
	return !(itr == connectionNodes.end());
}

bool BlockchainNode::
connect(BlockchainNode& node) {

	/* Verifico si existe o no ya */
	if (isConnectedTo(node)) {

		return true;
	}
	else {

		/* Agrego el nodo */
		try {
			connectionNodes.push_back(&node);

			return true;
		}
		catch (...) {

			return false;
		}
	}
}

bool BlockchainNode::
disconnect(BlockchainNode& node) {

	/* Verficio si esta */
	if (isConnectedTo(node)) {

		try {
			connectionNodes.remove(&node);

			return true;
		}
		catch (...) {

			return false;
		}
	}
	else {

		return false;
	}
}

bool BlockchainNode::
receive(BlockchainMessage& msg) {

	deque<BlockchainMessage>::iterator itr;

	/* Verifico no haberlo recibido ya */
	itr = find(msgQueue.begin(), msgQueue.end(), msg);

	if (itr == msgQueue.end()) {

		/* Agrego el mensaje */
		msgQueue.push_back(msg);

		return true;
	}

	return false;
}

void BlockchainNode::
sendAll(BlockchainMessage& msg) {

	/* Itero sobre todos los nodos conectados */
	for (BlockchainNode* node : connectionNodes) {

		if (node->receive(msg)) {

			node->sendAll(msg, *this);
		}
	}
}

void BlockchainNode::
sendAll(BlockchainMessage& msg, BlockchainNode& exceptNode) {

	/* Itero todos menos ese */
	for (BlockchainNode* node : connectionNodes) {

		if (*node != exceptNode) {

			if (node->receive(msg)) {

				node->sendAll(msg);
			}
		}
	}
}

ECDSA<ECP, SHA256>::PublicKey BlockchainNode::
getPublicKey(void) {

	return publicKey;
}

ECDSA<ECP, SHA256>::PrivateKey BlockchainNode::
getPrivateKey(void) {

	return privateKey;
}

bool BlockchainNode::
getNextMessage(BlockchainMessage& recv) {

	/* Verifico que este vacia */
	if (msgQueue.empty()) {

		return false;
	}
	else {

		/* Guardo mensaje */
		recv = msgQueue.front();

		/* Remuevo mensaje */
		msgQueue.pop_front();

		return true;
	}
}

bool BlockchainNode::
sendBuffer(BlockchainMessage& msg) {

	/* Verifico que no este ya agregado */
	if (find(msgBuffer.begin(), msgBuffer.end(), msg) == msgBuffer.end()) {

		/* Lo agrego */
		try {

			msgBuffer.push_back(msg);

			return true;
		}
		catch (...) {

			return false;
		}
	}

	return true;
}

void BlockchainNode::
release(void) {

	/* Verifico que hayan mensajes */
	if (!msgBuffer.empty()) {

		/* Busca el mensaje del frente */
		BlockchainMessage msg = msgBuffer.front();

		/* Saco el mensaje */
		msgBuffer.pop_front();

		/* Mando a todos el mensaje */
		sendAll(msg);
	}
}

unsigned int BlockchainNode::
get_posx(void)
{
	return pos_x;
}

unsigned int BlockchainNode::
get_posy(void)
{
	return pos_y;
}

unsigned int BlockchainNode::
get_radius(void)
{
	return radius;
}

void BlockchainNode::
set_properties(unsigned int posx_, unsigned int posy_, unsigned int radius_) {

	pos_x = posx_;
	pos_y = posy_;
	radius = radius_;

	_change_status();
}

bool BlockchainNode::
isInsideCircle(unsigned int px, unsigned int py)
{
	bool ret = false;
	unsigned int deltaX = (pos_x - px), deltaY = (pos_y - py);

	if (((deltaX*deltaX) + (deltaY*deltaY)) <= (radius*radius))
	{
		ret = true;
	}

	return ret;
}

unsigned int BlockchainNode::
getStatus(void) {

	return status;
}

void BlockchainNode::
_change_status(void) {

	notifyObservers();
}

void BlockchainNode::
_change_status(unsigned int newStatus) {

	/* Cambio el estado */
	status = newStatus;

	_change_status();
}