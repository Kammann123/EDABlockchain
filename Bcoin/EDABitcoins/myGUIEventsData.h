#pragma once
#include "PositionVector.h"
#include "allegro5/allegro.h"

class myGUIEventsData
{
public:
	myGUIEventsData();
	~myGUIEventsData();
	PositionVector get_mousePos();
	char get_keyPressed();
	void set_keyPressed(int key);
	void set_mousePos(unsigned int x, unsigned int y);
	void set_mousePos(PositionVector mousePos);
	void set_display(ALLEGRO_DISPLAY * display);
	ALLEGRO_DISPLAY * get_display();


private:
	PositionVector mousePos;
	ALLEGRO_DISPLAY * display;
	int keyPressed;
};

