#include "Graph.h"

#include <string>
#include <iostream>

using namespace std;

vector<bool> Graph::
_create_node(unsigned int count) {

	vector<bool> newVector;

	for (unsigned int i = 0; i < count; i++) {

		newVector.push_back(false);
	}

	return newVector;
}

void Graph::
addNode(void) {

	/* Nueva cantidad */
	numberOfNodes++;

	/* Agrego a los nodos actuales el nuevo nodo */
	for (vector<bool>& node : nodes) {

		node.push_back(false);
	}

	/* Agrego su marca */
	marks.push_back(false);

	/* Creo el nuevo nodo y lo agrego */
	nodes.push_back(_create_node(numberOfNodes));
}

void Graph::
addNode(unsigned int count) {

	while(count != 0){
	
		/* Agrego un nuevo nodo */
		addNode();

		/* Bajo el contador */
		count--;
	}
}

Graph::
Graph(unsigned int numberOfNodes) {

	this->numberOfNodes = 0;
	this->addNode(numberOfNodes);
}

Graph::
Graph(void) {

	this->numberOfNodes = 0;
	this->nodes.clear();
	this->marks.clear();
}

Graph::
~Graph() {

	/* Nothing to do */
}

bool Graph::
addConnection(unsigned int from, unsigned int to) {

	/* Verifico validez */
	if (from < numberOfNodes && to < numberOfNodes) {

		/* Busco y agrego la conexion en ambos */
		nodes[from][to] = true;
		nodes[to][from] = true;

		return true;
	}
	else {

		return false;
	}
}

bool Graph::
removeConnection(unsigned int from, unsigned int to) {

	/* Verifico validez */
	if (from < numberOfNodes && to < numberOfNodes) {

		/* Elimino la conexion */
		nodes[from][to] = false;
		nodes[to][from] = false;

		return true;
	}
	else {

		return false;
	}
}

unsigned int Graph::
getNumberOfNodes(void) {

	return this->numberOfNodes;
}

vector<unsigned int> Graph::
getNeighbours(unsigned int v) {

	vector<unsigned int> neighbours;
	unsigned int i = 0;

	/* Busco entre los del nodo los conectados */
	for (bool c : nodes[v]) {

		/* Si estas conectado */
		if (c) {

			neighbours.push_back(i);
		}

		/* Proximo nodo */
		i++;
	}

	return neighbours;
}

void Graph::
clearConnections(void) {

	/* Voy por todos y los borro */
	for (unsigned int i = 0; i < numberOfNodes; i++) {

		for (unsigned int j = 0; j < numberOfNodes; j++) {

			nodes[i][j] = false;
		}
	}
}

void Graph::
display(void) {

	/* Voy uno por uno y lo pongo */
	for (unsigned int i = 0; i < numberOfNodes; i++) {

		for (unsigned int j = 0; j < numberOfNodes; j++) {

			cout << to_string(nodes[i][j] ? 1 : 0) << " ";
		}

		cout << endl;
	}
}

void Graph::
_clear_marks(void) {

	for (unsigned int i = 0; i < numberOfNodes; i++) {

		marks[i] = false;
	}
}

void Graph::
_visit_nodes(unsigned int from) {

	vector<unsigned int> neighbours = getNeighbours(from);
	vector<unsigned int> visit;

	/* Marco visitado */
	marks[from] = true;

	/* Descarto los que ya fueron visitados */
	for (unsigned int neighbour : neighbours) {

		/* Si no lo visito */
		if (!marks[neighbour]) {
			visit.push_back(neighbour);
		}
	}

	/* Si queda alguien por visitar */
	if (!visit.empty()) {

		/* Los visito */
		for (unsigned int v : visit) {

			/* Si no fue visitado */
			if (!marks[v]) {
				_visit_nodes(v);
			}
		}
	}
}

bool Graph::
isConnected(void) {

	/* Limpio las marcas */
	_clear_marks();

	/* Visito las marcas */
	_visit_nodes(0);

	/* Verifico cuales fueron visitados */
	for (bool b : marks) {

		if (!b) {

			return false;
		}
	}

	return true;
}

void Graph::
setRandomConnected(void) {

	/* Limpio las conexiones */
	clearConnections();

	/* Para cada nodo */
	for (unsigned int i = 0; i < numberOfNodes; i++) {

		/* Me fijo que no tenga ya dos aristas */
		if (getNeighbours(i).size() >= 2) {
			continue;
		}

		/* Agrego dos aristas */
		unsigned int j = 2;
		while (j) {

			/* Si ya es conexo me voy... */
			if (isConnected()) {
				return;
			}

			/* Busco un vecino */
			unsigned int n = _random_neighbour(i);

			/* Me fijo que no este conectado con 2 o mas */
			if (getNeighbours(n).size() >= 2) {
				continue;
			}

			/* Me fijo que no esten conectados entre si ya */
			if (nodes[i][n]) {
				continue;
			}

			/* Los conecto */
			addConnection(i, n);

			/* Paso a la siguiente arista */
			j--;
		}
	}

	/* Luego verifico que sea conexo */
	while (!isConnected()) {

		/* Busco las marcas que no estan y uno alguno */
		for (unsigned int i = 0; i < numberOfNodes; i++) {

			/* No fue recorrido */
			if (!marks[i]) {

				/* Agrego conexion con este */
				addConnection(0, i);
				break;
			}
		}
	}
}

unsigned int Graph::
_random_neighbour(unsigned int from) {

	vector<unsigned int> neighbours = getNeighbours(from);
	vector<unsigned int> unknown;

	/* Nuevo vector con opciones */
	for (unsigned int i = 0; i < numberOfNodes; i++) {

		if (find(neighbours.begin(), neighbours.end(), i) == neighbours.end()) {

			unknown.push_back(i);
		}
	}

	/* Genero un numero aleatorio */
	unsigned int n = unknown[ rand() % unknown.size() ];

	return n;
}