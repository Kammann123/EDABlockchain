#include "../stdafx.h"
#include "ALL_BUTTON_CONTROLLER.h"

void ALL_BUTTON_CONTROLLER::
parseCloseEvent(myGUIEventsData*  newEvent) {}

ALL_BUTTON_CONTROLLER::ALL_BUTTON_CONTROLLER(ALL_BUTTON * buttonToControl)
{
	this->buttonToControl = buttonToControl;
}

void ALL_BUTTON_CONTROLLER::parseMouseEvent(myGUIEventsData * newEvent)
{
	if (buttonToControl->isPointInsideRect(newEvent->get_mousePos()))
		buttonToControl->set_action_flag(true);
}

void ALL_BUTTON_CONTROLLER::parseKeyboardEvent(myGUIEventsData * newEvent)
{
}

ALL_BUTTON_CONTROLLER::~ALL_BUTTON_CONTROLLER()
{
}
