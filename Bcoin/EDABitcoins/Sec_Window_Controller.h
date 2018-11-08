#pragma once
#include "Sec_Window_View.h"
#include "Controller.h"

class Sec_Window_Controller: public Controller
{
public:
	Sec_Window_Controller(Sec_Window_View* view);	//Constructor
	~Sec_Window_Controller();		//Destructor

	

	// Instancias concretas de las funciones abstractas de Controller
	void parseCloseEvent(myGUIEventsData * newEvent);
	void parseMouseEvent(myGUIEventsData * newEvent);
	void parseKeyboardEvent(myGUIEventsData *  newEvent);
	
	Sec_Window_View* getView();//Devuelve view que controla

private:
	Sec_Window_View * windowToControl;	//View que controla
};

