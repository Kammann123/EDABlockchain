#pragma once
#include "../Controller.h"
#include "ALL_BUTTON.h"
class ALL_BUTTON_CONTROLLER:public Controller
{
public:
	ALL_BUTTON_CONTROLLER(ALL_BUTTON * buttonToControl);
	// Instancias concretas de las funciones abstractas declaradas arriba
	void parseMouseEvent(myGUIEventsData * newEvent);
	void parseKeyboardEvent(myGUIEventsData *  newEvent);
	void parseCloseEvent(myGUIEventsData*  newEvent);
	~ALL_BUTTON_CONTROLLER();

private:
	ALL_BUTTON * buttonToControl;
};


