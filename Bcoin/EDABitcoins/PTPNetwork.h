#pragma once

#include "blockchain_actors/ActorFactory.h"
#include "Graph.h"
#include "Graphics.h"
#include "Controller.h"
#include "Subject.h"
#include <map>

using namespace std;

/* 
* PTPNetwork
*
* Modelizacion de la red peer to peer con todos los nodos que se deseen de cada tipo.
*
*/
class PTPNetwork : public Subject{

public:

	/*
	* Constructores y destructores
	*
	* fullserviceCount, minerCount: Cantidad de nodos de cada tipo de la red
	*/
	PTPNetwork(unsigned int fullserviceCount, unsigned int minerCount, Graphics& graphics);
	~PTPNetwork();
	
	/*
	* getNodes
	* 
	* Devuelve el diccionario con los nodos del sistema
	*
	* Recibis nodes. Y cuando haces nodes[id] te da el nodo.
	* Le preguntas a nodes los keys que hay.
	*
	*/
	map<unsigned int, BlockchainNode*> getNodes(void);

	/*
	* getNodeNeighbours
	*
	* Devuelve un vector con los nodos vecinos a uno.
	*/
	vector<unsigned int> getNodeNeighbours(unsigned int nodeId);

	/*
	* displayBalance
	*
	* Le pide al nodo con nodeID que despliegue la informacion del balance
	* de todos los nodos de la red.
	*
	* nodeID: Numero dentro del grafo del nodo
	*/
	void displayBalance(unsigned int nodeID);
	void displayBalance(void);
	void displayGraph(void);

	/*
	* transfer / fake_transfer
	*
	* fromID, toID: De y para quienes 
	* amount: Monedas
	* fee: Lo que le deja al minero
	*/
	bool transfer(unsigned int fromID, unsigned int toID, double amount, double fee = 0);
	bool fake_transfer(unsigned int fromID, unsigned int toID, double amount, double fee = 0);

	/*
	* genesis
	*
	* Inicia todo el primer bloque, el de genesis.
	*
	* nodeID: Nodo al cual se le da el primer monto.
	* sendID: Nodo que lo manda
	* amount: Monto inicial
	*/
	void genesis(unsigned int nodeID, unsigned int sendID, double amount);
	void genesis(unsigned int nodeID, double amount);

	/*
	* run
	*
	* Ejecuta operaciones de la red
	*/
	void run(void);

	/*
	* getNodesController
	*
	* Devuelve controlador de nodos
	*/
	vector<Controller*> getNodesControllers(void);
	vector<Controller*> getSecControllers(void);

	/*
	* getNodeId
	* 
	* Devuelve el id del nodo loco!
	*/
	int getNodeId(BlockchainNode* node);

private:

	map<unsigned int, BlockchainNode*> nodes;
	vector<Controller*> nodesControllers;
	vector<Controller*> secControllers;
	Graph graph;
	unsigned int minerCount, fullserviceCount, nodesCount;
	unsigned int runID;
};