#include "blockchain_actors/FullService.h"
#include "blockchain_actors/Miner.h"
#include "blockchain/cryptoeda.h"
#include "PTPNetworkView.h"
#include "PTPNetwork.h"
#include "Graph.h"
#include "Graphics.h"
#include "GUI.h"
#include <chrono>
#include <thread>
#include <conio.h>
#include <iostream>

using namespace std;
using namespace cryptoeda;

int main(int argc, char** argv) {

	/* Creo e inicializo los bellos objetos */
	Graphics graphics(1000, 750);
	PTPNetwork network(4, 2, graphics);
	PTPNetworkView networkView(network);
	network.attach(&networkView);
	GUI gui;

	/* Agrego los controladores */
	for (Controller* controller : network.getNodesControllers()) {
		gui.addNewGUIController(controller);
	}

	for (Controller* controller : network.getSecControllers()) {
		gui.addNewGUIController(controller);
	}

	/* Inicializo la red */
	network.genesis(1, 50);
	bool exit = false;
	/* Loop infinito (? */
	while (!exit) {

		/* Parseo eventos */
		if (gui.hasEvent()) {	//Hay evento?
			exit = gui.exit(graphics.getDisplay());
			if(!exit)			//Es evento de salida>
				gui.parseEvent();	//Se parsea
		}

		/* Le doy al tipo el run */
		network.run();
	}
}