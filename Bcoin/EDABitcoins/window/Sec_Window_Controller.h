#pragma once
#include "Sec_Window.h"
class Sec_Window_Controller: public Controller
{
public:
	Sec_Window_Controller(Sec_Window * windowToControl);
	// Instancias concretas de las funciones abstractas declaradas arriba
	void parseMouseEvent(myGUIEventsData * newEvent);
	void parseKeyboardEvent(myGUIEventsData *  newEvent);
	void update_info();
	~Sec_Window_Controller();

private:
	Sec_Window * windowToControl;
};

