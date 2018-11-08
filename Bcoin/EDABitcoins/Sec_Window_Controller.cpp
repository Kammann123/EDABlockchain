#include "stdafx.h"
#include "Sec_Window_Controller.h"

Sec_Window_View* Sec_Window_Controller::
getView(void) {

	return windowToControl;
}

Sec_Window_Controller::Sec_Window_Controller(Sec_Window_View * windowToControl)
{
	this->windowToControl = windowToControl;
}

void Sec_Window_Controller::parseMouseEvent(myGUIEventsData * newEvent)
{
	if (windowToControl->get_display()) {
		if (newEvent->get_display() == windowToControl->get_display())
		{
			windowToControl->get_sendTransfController()->parseMouseEvent(newEvent);
			windowToControl->get_sendMalTransfController()->parseMouseEvent(newEvent);
			windowToControl->get_transferenceToController()->parseMouseEvent(newEvent);
			windowToControl->get_transferenceAmountController()->parseMouseEvent(newEvent);
			windowToControl->get_feeAmountController()->parseMouseEvent(newEvent);

			if (windowToControl->get_sendTransference()->get_action_flag())
			{
				//EJECUTAR TRANSFERENCIA
				windowToControl->get_network()->transfer(windowToControl->get_network()->getNodeId(windowToControl->get_node()), 
														stoi(windowToControl->get_transferenceTo()->get_text()), 
														stod(windowToControl->get_transferenceAmount()->get_text(), NULL),
														stod(windowToControl->get_feeAmount()->get_text(),NULL));
				windowToControl->get_sendTransference()->set_action_flag(false);
				windowToControl->get_transferenceTo()->set_text("");
				windowToControl->get_transferenceAmount()->set_text("");

			}
			if (windowToControl->get_sendMalTransference()->get_action_flag())
			{
				//EJECUTAR TRANSFERENCIA MALICIOSA
				windowToControl->get_network()->fake_transfer(windowToControl->get_network()->getNodeId(windowToControl->get_node()),
															stoi(windowToControl->get_transferenceTo()->get_text()), 
															stod(windowToControl->get_transferenceAmount()->get_text(), NULL), 
															stod(windowToControl->get_feeAmount()->get_text(), NULL));
				windowToControl->get_sendMalTransference()->set_action_flag(false);
				windowToControl->get_transferenceTo()->set_text("");
				windowToControl->get_transferenceAmount()->set_text("");
			}
			windowToControl->update();
		}
		else
		{
			windowToControl->get_transferenceToController()->disable_editText();
			windowToControl->get_transferenceAmountController()->disable_editText();
			windowToControl->get_feeAmountController()->disable_editText();
		}
	}
}

void Sec_Window_Controller::parseKeyboardEvent(myGUIEventsData * newEvent)
{
	if (windowToControl->get_display()) {

		windowToControl->get_transferenceToController()->parseKeyboardEvent(newEvent);
		windowToControl->get_transferenceAmountController()->parseKeyboardEvent(newEvent);
		windowToControl->get_feeAmountController()->parseKeyboardEvent(newEvent);
		windowToControl->update();
	}
}

Sec_Window_Controller::~Sec_Window_Controller()
{
}

void Sec_Window_Controller::parseCloseEvent(myGUIEventsData * newEvent)
{
	if (windowToControl->get_display()) {
		if (newEvent->get_display() == windowToControl->get_display())
		{
			windowToControl->hide();
		}
	}
}