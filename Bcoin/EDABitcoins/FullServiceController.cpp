#include "FullServiceController.h"

FullServiceController::FullServiceController(FullService& node_, FullServiceView& view_, Graphics& graphics_) :node(node_), nodeView(view_), graphics(graphics_) {}

FullServiceController::~FullServiceController() {}

void FullServiceController::
parseKeyboardEvent(myGUIEventsData* ev_) {

}

void FullServiceController::parseCloseEvent(myGUIEventsData * newEvent)
{
}

void FullServiceController::
parseMouseEvent(myGUIEventsData* ev_)
{
	if ((ev_->get_display() == graphics.getDisplay()) && (node.isInsideCircle(ev_->get_mousePos().get_x(), ev_->get_mousePos().get_y()))) // si el click corresponde al display donde se muestran los nodos, y es dentro del nodo
	{
		node.toggleSelection(); // cambio el estado de selección del nodo
	}
}

FullService * FullServiceController::
getNode(void)
{
	return &node;
}

FullServiceView* FullServiceController::
getNodeView(void) {

	return &nodeView;
}