#pragma once

#include "BlockchainMessage.h"
#include "../blockchain/cryptoeda.h"
#include "../Subject.h"

#include <list>
#include <deque>

using namespace CryptoPP;
using namespace std;

/*
* BlockchainNode
*
* Esta clase modela los nodos de la red peer to peer del blockchain,
* administrando la forma en que tales nodos se conectan entre si y 
* luego se comunican.
*/
class BlockchainNode: public Subject {

public:

	/*
	* Constructores y destructores de BlockchainNode
	*/
	BlockchainNode();
	BlockchainNode(ECDSA<ECP, SHA256>::PrivateKey privateKey);
	~BlockchainNode();

	/*
	* Sobrecarga de operaciones
	*/
	bool operator==(const BlockchainNode& node);
	bool operator!=(const BlockchainNode& node);
	const BlockchainNode& operator=(const BlockchainNode& node);

	/*
	* connect
	* Conecta al nodo con otro nodo
	*
	* node: Nodo al cual se conecta
	*/
	bool connect(BlockchainNode& node);

	/*
	* disconnect
	* Desconecta al nodo
	*
	* node: Nodo del cual se desconecta
	*/
	bool disconnect(BlockchainNode& node);

	/*
	* sendAll
	* Manda un mensaje a todos los nodos conectados
	*
	* msg: Mensaje que se manda
	*/
	void sendAll(BlockchainMessage& msg);
	void sendAll(BlockchainMessage& msg, BlockchainNode& exceptNode);

	/*
	* sendBuffer
	* Manda al buffer de salida un mensaje
	*
	* msg: Mensaje para el buffer de salida
	*/
	bool sendBuffer(BlockchainMessage& msg);

	/*
	* release
	* Libera un mensaje del buffer de salida, para todos o un
	* nodo segun que version de sobrecarga se este usando.
	*
	* node: Nodo al que manda
	*/
	void release(void);

	/*
	* receive
	* Recibo un mensaje de algun nodo
	*
	* msg: Mensaje recibido
	*/
	bool receive(BlockchainMessage& msg);

	/*
	*
	* getPublicKey/getPrivateKey
	*
	* Devuelve las claves publica y privada del nodo
	*/
	ECDSA<ECP, SHA256>::PublicKey getPublicKey(void);
	ECDSA<ECP, SHA256>::PrivateKey getPrivateKey(void);

	/*
	*
	* getNextMessage
	*
	* Devuelve el proximo mensaje en la cola de la capa de comunicacion en la
	* variable recibida. Si devuelve true, hubo mensaje!
	*
	* recv: Donde se guarda el mensaje
	*/
	bool getNextMessage(BlockchainMessage& recv);

	/*
	* 
	* getType
	*
	* Devuelve el tipo de nodo
	*/
	virtual unsigned int getType(void) = 0;

	/*
	*
	* get_posx
	*
	* Devuelve la posición en display del nodo, sobre el eje x (getter)
	*/
	unsigned int get_posx(void);

	/*
	*
	* get_posy
	*
	* Devuelve la posición en display del nodo, sobre el eje y (getter)
	*/
	unsigned int get_posy(void);

	/*
	*
	* get_radius
	*
	* Devuelve el radio del nodo
	*/
	unsigned int get_radius(void);

	/*
	*
	* set_properties
	*/
	void set_properties(unsigned int posx_, unsigned int posy_, unsigned int radius_);

	/*
	*
	* isInsideCircle
	*
	* Verifica si un punto está dentro del nodo circular
	*/
	bool isInsideCircle(unsigned int px, unsigned int py);

	/*
	*
	* getStatus
	*
	* Devuelve el estado actual de operacion del FullService
	*/
	unsigned int getStatus(void);

protected:

	/* 
	* isConnectedTo
	* Devuelve true si esta conectado al nodo
	*
	* node: Nodo
	*/
	bool isConnectedTo(BlockchainNode& node);

	void _change_status(unsigned int newStatus);
	void _change_status(void);

	ECDSA<ECP, SHA256>::PublicKey publicKey;
	ECDSA<ECP, SHA256>::PrivateKey privateKey;
	deque<BlockchainMessage> msgQueue;
	deque<BlockchainMessage> msgBuffer;
	list<BlockchainNode*> connectionNodes;

	unsigned int status;

	unsigned int pos_x;
	unsigned int pos_y;
	unsigned int radius;
};