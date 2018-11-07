#include "PTPNetworkView.h"

PTPNetworkView::
PTPNetworkView(PTPNetwork& network_) : network(network_) {}

PTPNetworkView::~PTPNetworkView() {}

void PTPNetworkView::
update(void)
{

	map<unsigned int, BlockchainNode*> nodes = network.getNodes();

	for (unsigned int i = 0; i < nodes.size(); i++)
	{
		vector<unsigned int> neighbourList = network.getNodeNeighbours(i);

		for (unsigned int j = 0; j < neighbourList.size(); j++)
		{

			BlockchainNode* nodeDest = ((BlockchainNode*)nodes[(neighbourList[j])]); // obtengo puntero a nodo adyacente al actual
			unsigned int xSource = ((BlockchainNode*)nodes[i])->get_posx(); // obtengo posicion x del nodo actual
			unsigned int ySource = ((BlockchainNode*)nodes[i])->get_posy();; // obtengo posicion y del nodo actual
			unsigned int xDest = nodeDest->get_posx(); // obtengo posicion x de un nodo adyacente al actual
			unsigned int yDest = nodeDest->get_posy(); // obtengo posicion y de un nodo adyacente al actual

			al_draw_line(xSource, ySource, xDest, yDest, LINE_COLOR, LINE_THICKNESS); // dibujo líneas que unan ambos nodos
		}
	}
	
	al_flip_display();

	for (Controller* controller : network.getNodesControllers()) {

		((FullServiceController*)controller)->getNodeView()->update();
	}
}