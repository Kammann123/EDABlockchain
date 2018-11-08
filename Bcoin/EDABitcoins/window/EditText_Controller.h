#pragma once
#include "../Controller.h"
#include "EditText.h"
class EditText_Controller : public Controller
{
public:
	EditText_Controller(EditText * editTextToControl);
	// Instancias concretas de las funciones abstractas declaradas arriba
	void parseMouseEvent(myGUIEventsData * newEvent);
	void parseKeyboardEvent(myGUIEventsData *  newEvent);
	void parseCloseEvent(myGUIEventsData*  newEvent);
	~EditText_Controller();
	void disable_editText();

private:
	EditText * editTextToControl;
};

