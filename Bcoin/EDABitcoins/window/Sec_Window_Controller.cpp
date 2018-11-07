#include "stdafx.h"
#include "Sec_Window_Controller.h"



Sec_Window_Controller::Sec_Window_Controller(Sec_Window * windowToControl)
{
	this->windowToControl = windowToControl;
}

void Sec_Window_Controller::parseMouseEvent(myGUIEventsData * newEvent)
{
	if (newEvent->get_display() == windowToControl->get_display())
	{
		windowToControl->get_sendTransfController()->parseMouseEvent(newEvent);
		windowToControl->get_sendMalTransfController()->parseMouseEvent(newEvent);
		windowToControl->get_transferenceToController()->parseMouseEvent(newEvent);
		windowToControl->get_transferenceAmountController()->parseMouseEvent(newEvent);

		if (windowToControl->get_sendTransference()->get_action_flag())
		{
			//EJECUTAR TRANSFERENCIA
			windowToControl->get_network()->transfer(windowToControl->get_nodeId(), stoi(windowToControl->get_transferenceTo()->get_text()), stod(windowToControl->get_transferenceAmount()->get_text(),NULL), 10);
			windowToControl->get_sendTransference()->set_action_flag(false);
			windowToControl->get_transferenceTo()->set_text("");
			windowToControl->get_transferenceAmount()->set_text("");

		}
		if (windowToControl->get_sendMalTransference()->get_action_flag())
		{
			//EJECUTAR TRANSFERENCIA MALICIOSA
			windowToControl->get_network()->fake_transfer(windowToControl->get_nodeId(), stoi(windowToControl->get_transferenceTo()->get_text()), stod(windowToControl->get_transferenceAmount()->get_text(),NULL), 10);
			windowToControl->get_sendMalTransference()->set_action_flag(false);
			windowToControl->get_transferenceTo()->set_text("");
			windowToControl->get_transferenceAmount()->set_text("");
		}
		windowToControl->notifyAllObservers();
	}
	else
	{
		windowToControl->get_transferenceToController()->disable_editText();
		windowToControl->get_transferenceAmountController()->disable_editText();
	}
}

void Sec_Window_Controller::parseKeyboardEvent(myGUIEventsData * newEvent)
{
	windowToControl->get_transferenceToController()->parseKeyboardEvent(newEvent);
	windowToControl->get_transferenceAmountController()->parseKeyboardEvent(newEvent);
	windowToControl->notifyAllObservers();
}

Sec_Window_Controller::~Sec_Window_Controller()
{
}

void Sec_Window_Controller::update_info()
{
	FullService * node = windowToControl->get_node();
	string type, state;
	(node->getType() == MINER_TYPE) ? type = "MINERO" : type = "FULL SERVICE";
	if ((node->getStatus()) == (IDLE))
		state = "ESPERANDO";
	else if ((node->getStatus()) == PENDING_MSG)
		state = "MENSAJE PENDIENTE";
	else
		state = "PROCESANDO MENSAJE";
	windowToControl->get_nodeTypeText()->set_text(type);
	windowToControl->get_nodeStateText()->set_text(state);
	

}