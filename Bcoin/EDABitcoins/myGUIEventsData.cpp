#include "stdafx.h"
#include "myGUIEventsData.h"

myGUIEventsData::myGUIEventsData()
{
}

myGUIEventsData::~myGUIEventsData()
{
}

PositionVector myGUIEventsData::get_mousePos()
{
	return mousePos;
}

char myGUIEventsData::get_keyPressed()
{
	return keyPressed;
}

void myGUIEventsData::set_keyPressed(int key)
{
	keyPressed = key;
}

void myGUIEventsData::set_mousePos(unsigned int x, unsigned int y)
{
	mousePos.set_x(x);
	mousePos.set_y(y);
}

void myGUIEventsData::set_mousePos(PositionVector  mousePos)
{
	(this->mousePos) = mousePos;
}

void myGUIEventsData::set_display(ALLEGRO_DISPLAY *  display)
{
	(this->display) = display;
}

ALLEGRO_DISPLAY * myGUIEventsData::get_display()
{
	return display;
}
