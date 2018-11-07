#include "PTPNetwork.h"
#include "circPosFactory.h"
#include "Sec_Window_Controller.h"
#include "Sec_Window_View.h"

PTPNetwork::
PTPNetwork(unsigned int fullserviceCount, unsigned int minerCount, Graphics& graphics) : graph(minerCount+fullserviceCount) {

	/* Inicio seed */
	srand((unsigned int)time(NULL));

	/* Configuro las cantidades */
	this->fullserviceCount = fullserviceCount;
	this->minerCount = minerCount;
	this->nodesCount = minerCount + fullserviceCount;
	this->runID = 0;

	/* Creo el grafo conexo */
	graph.setRandomConnected();

	/* Creo todos los nodos */
	for (unsigned int i = 0; i < nodesCount; i++) {

		/* Agrego el nodo */
		if (fullserviceCount) {

			/* Agrego fullservice */
			FullServiceController* controller = ActorFactory::create(FULLSERVICE_TYPE, graphics);

			if (controller) {
				BlockchainNode* node = controller->getNode();

				Sec_Window_View* secView = new Sec_Window_View((FullService*)node, this);
				Sec_Window_Controller* secController = new Sec_Window_Controller(secView);

				node->attach(secView);

				nodes.insert(pair<unsigned int, BlockchainNode*>(i, node));
				nodesControllers.push_back(controller);

				secControllers.push_back(secController);

				/* Ya agregue un fullservice */
				fullserviceCount--;
			}

		} else{

			FullServiceController* controller = ActorFactory::create(MINER_TYPE, graphics);
			
			if (controller) {
				BlockchainNode* node = controller->getNode();

				Sec_Window_View* secView = new Sec_Window_View((FullService*)node, this);
				Sec_Window_Controller* secController = new Sec_Window_Controller(secView);

				node->attach(secView);

				nodes.insert(pair<unsigned int, BlockchainNode*>(i, node));
				nodesControllers.push_back(controller);

				secControllers.push_back(secController);
			}
		}
	}

	/* Conecto todos los nodos */
	for (unsigned int i = 0; i < nodesCount; i++) {

		/* Busco a quien se conecta */
		vector<unsigned int> neighbours = graph.getNeighbours(i);

		/* Entre los vecinos, conecto con el nodo */
		for (unsigned int j = 0; j < neighbours.size(); j++) {

			nodes[i]->connect(*nodes[neighbours[j]]);
		}
	}

	/* Asigno posiciones aleatorias */
	circPosFactory joacoFactory(this->nodesCount, graphics.getWidth() / 2, graphics.getHeight() / 2, graphics.getWidth() / 4);
	unsigned int x, y;
	for (auto const& nodePair : nodes) {

		/* Configuro el nodo buscando la posicion primero */
		if (joacoFactory.getNextPos(x, y)) {

			/* Le seteo las cosas */
			nodePair.second->set_properties(x, y, 20);
		}
	}
}

PTPNetwork::
~PTPNetwork() {

	/* Limpio la memoria usada */
	for (Controller* controller : nodesControllers) {
		ActorFactory::destroy((FullServiceController*)controller);
	}

	for (Controller* controller : secControllers) {

		delete ((Sec_Window_Controller*)controller)->getView();
		delete controller;
	}
}

map<unsigned int, BlockchainNode*> PTPNetwork::
getNodes(void) {
	return this->nodes;
}

void PTPNetwork::
displayBalance(void) {

	for (unsigned int i = 0; i < nodesCount; i++) {

		displayBalance(i);

		cout << endl;
	}
}

void PTPNetwork::
displayBalance(unsigned int nodeID) {

	if (nodeID >= nodesCount) {

		return;
	}

	cout << "[Informacion de balance] - Por nodo " << to_string(nodeID) << endl << endl;

	FullService* node = (FullService*)nodes[nodeID];

	for (unsigned int i = 0; i < nodesCount; i++) {

		FullService* nNode = (FullService*)nodes[i];

		double balance = node->balance(nNode->getPublicKey());

		string type = nNode->getType() == FULLSERVICE_TYPE ? "FullService" : "Miner";

		cout << "[ " << type << " - " << to_string(i) << "]" << " Tiene " << to_string(balance) << " EDACoins." << endl;
	}
}

vector<unsigned int> PTPNetwork::
getNodeNeighbours(unsigned int nodeId) {

	return this->graph.getNeighbours(nodeId);
}

void PTPNetwork::
genesis(unsigned int nodeID, unsigned int sendID, double amount) {

	if (nodeID >= nodesCount || sendID >= nodesCount) {
		return;
	}

	FullService* to = (FullService*)nodes[nodeID];
	FullService* from = (FullService*)nodes[sendID];

	from->genesis(to->getPublicKey(), amount);
}

void PTPNetwork::
genesis(unsigned int nodeID, double amount) {

	genesis(nodeID, nodeID, amount);

	notifyObservers();
}

void PTPNetwork::
run(void) {

	FullService* node = (FullService*)nodes[runID++];

	if (runID >= nodesCount) {
		runID = 0;
	}

	node->run();
}

bool PTPNetwork::
transfer(unsigned int fromID, unsigned int toID, double amount, double fee) {

	if (fromID >= nodesCount || toID >= nodesCount) {
		return false;
	}

	FullService* from = (FullService*)nodes[fromID];
	FullService* to = (FullService*)nodes[toID];

	return from->transfer(
		from->getPublicKey(),
		to->getPublicKey(),
		from->getPrivateKey(),
		amount,
		fee
	);
}

bool PTPNetwork::
fake_transfer(unsigned int fromID, unsigned int toID, double amount, double fee) {
	
	if (fromID >= nodesCount || toID >= nodesCount) {
		return false;
	}

	FullService* from = (FullService*)nodes[fromID];
	FullService* to = (FullService*)nodes[toID];

	return from->transfer(
		from->getPublicKey(),
		to->getPublicKey(),
		amount,
		fee
	);
}

void PTPNetwork::
displayGraph(void) {

	graph.display();
}

vector<Controller*> PTPNetwork::
getNodesControllers(void) {

	return nodesControllers;
}

int PTPNetwork::
getNodeId(BlockchainNode* node) {

	for (auto const& nodePair : nodes) {

		if (nodePair.second == node) {
			
			return nodePair.first;
		}
	}

	return -1;
}

vector<Controller*> PTPNetwork::
getSecControllers(void) {

	return secControllers;
}