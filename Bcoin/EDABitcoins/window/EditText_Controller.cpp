#include "../stdafx.h"
#include "EditText_Controller.h"



EditText_Controller::EditText_Controller(EditText * editTextToControl)
{
	this->editTextToControl = editTextToControl;
}

void EditText_Controller::
parseCloseEvent(myGUIEventsData*  newEvent) {}

void EditText_Controller::parseMouseEvent(myGUIEventsData * newEvent)
{
	if (editTextToControl->isPointInsideRect(newEvent->get_mousePos()))
	{
		editTextToControl->set_focused(true);
		editTextToControl->set_backColor(al_map_rgb(0, 255, 0));
	}
	else {
		editTextToControl->set_focused(false);
		editTextToControl->set_backColor(al_map_rgb(255, 255, 255));
	}
		
}

void EditText_Controller::disable_editText()
{
	editTextToControl->set_focused(false);
}

void EditText_Controller::parseKeyboardEvent(myGUIEventsData * newEvent)
{
	if (editTextToControl->get_focused())
	{
		editTextToControl->new_number(newEvent->get_keyPressed());
	}
}

EditText_Controller::~EditText_Controller()
{
}
