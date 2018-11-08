#pragma once
#include <allegro5/allegro.h>

#include "myGUIEventsData.h"

class Controller
{
public:
	Controller() {};
	~Controller() {};
	virtual void parseMouseEvent(myGUIEventsData* ev_) = 0;
	virtual void parseKeyboardEvent(myGUIEventsData*  ev_) = 0;
	virtual void parseCloseEvent(myGUIEventsData*  ev_) = 0;
};