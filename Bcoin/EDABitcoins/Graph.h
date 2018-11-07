#pragma once

#include <vector>

using namespace std;

/*
* Graph
* 
* Clase para implementar el uso de grafos
*/
class Graph {

public:

	/*
	* Constructores y destructores
	*/
	Graph(unsigned int numberOfNodes);
	Graph(void);
	~Graph();

	/*
	* addNode
	*
	* Agrega nodo al grafo
	*/
	void addNode(void);
	void addNode(unsigned int count);

	/*
	* addConnection
	*
	* Agrega conexion entre dos nodos
	*
	* from, to: Numero de nodos a conectar
	*/
	bool addConnection(unsigned int from, unsigned int to);

	/*
	* removeConnection
	*
	* Remueve una conexion entre dos nodos
	*
	* from, to: Numero de nodos a desconectar
	*/
	bool removeConnection(unsigned int from, unsigned int to);

	/*
	* getNeighbours
	*
	* Devuelve listado de vecinos del nodo
	*
	* v: Numero del nodo
	*/
	vector<unsigned int> getNeighbours(unsigned int v);

	/*
	* getNumberOfNodes
	*
	* Devuelve la cantidad de nodos del grafo
	*
	*/
	unsigned int getNumberOfNodes(void);

	/*
	* isConnected
	*
	* Devuelve si el grafo es conexo
	*/
	bool isConnected(void);

	/*
	* setRandomConnected
	*
	* Establece conexiones aleatorias para hacer al grafo conexo
	*/
	void setRandomConnected(void);
	
	/*
	* clearConnections
	*
	* Elimina todas las conexiones del grafo
	*/
	void clearConnections(void);

	/*
	* display
	*
	* Muestra la tabla de adyacencia
	*/
	void display(void);

private:

	/*
	* _create_node
	*
	* Crea un nodo inicial
	*/
	vector<bool> _create_node(unsigned int count);

	void _clear_marks(void);
	void _visit_nodes(unsigned int from);
	unsigned int _random_neighbour(unsigned int from);

	vector<vector<bool>> nodes;
	vector<bool> marks;
	unsigned int numberOfNodes;
};