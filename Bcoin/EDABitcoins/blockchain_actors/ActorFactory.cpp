#include "ActorFactory.h"
#include "../Sec_Window_View.h"
#include "../Sec_Window_Controller.h"

void ActorFactory::
destroy(FullServiceController* controller) {

	FullService* node = controller->getNode();
	FullServiceView* nodeView = controller->getNodeView();

	/* Destruyo todo */
	delete node;
	delete nodeView;
	delete controller;
}

FullServiceController* ActorFactory::
create(unsigned int type, Graphics& graphics) {
	
	FullService* node;
	FullServiceView* view;
	FullServiceController* controller;

	switch (type) {

		case FULLSERVICE_TYPE:
			node = new FullService();
			break;

		case MINER_TYPE:
			node = new Miner();
			break;

		default:
			return nullptr;
			break;
	
	}

	view = new FullServiceView(*node, graphics);
	controller = new FullServiceController(*node, *view, graphics);

	node->attach(view); // attach del observer del nodo
	return controller;
}

FullServiceController* ActorFactory:: 
create(unsigned int type, Graphics& graphics, ECDSA<ECP, SHA256>::PrivateKey pKey) {

	FullService* node;
	FullServiceView* view;
	FullServiceController* controller;

	switch (type) {

	case FULLSERVICE_TYPE:
		node = new FullService(pKey);
		break;

	case MINER_TYPE:
		node = new Miner(pKey);
		break;

	default:
		return nullptr;
		break;

	}

	view = new FullServiceView(*node, graphics);
	controller = new FullServiceController(*node, *view, graphics);

	node->attach(view); // attach del observer del nodo
	return controller;
}