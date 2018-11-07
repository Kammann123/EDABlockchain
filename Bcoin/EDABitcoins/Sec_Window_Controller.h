#pragma once
#include "Sec_Window_View.h"
#include "Controller.h"

class Sec_Window_Controller: public Controller
{
public:
	Sec_Window_Controller(Sec_Window_View* view);
	~Sec_Window_Controller();

	// Instancias concretas de las funciones abstractas declaradas arriba
	void parseMouseEvent(myGUIEventsData * newEvent);
	void parseKeyboardEvent(myGUIEventsData *  newEvent);
	Sec_Window_View* getView();

private:
	Sec_Window_View * windowToControl;
};

