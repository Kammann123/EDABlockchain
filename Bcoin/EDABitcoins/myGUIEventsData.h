#pragma once
#include "PositionVector.h"
#include "allegro5/allegro.h"

class myGUIEventsData
{
public:
	//Guarda la informacion de un evento
	/*Constructor*/
	myGUIEventsData();
	/*Destructor*/
	~myGUIEventsData();
	/*Metodos*/
	PositionVector get_mousePos();		//Devuelve la posicion del mouse
	char get_keyPressed();				//Devuelve la tecla apretada
	void set_keyPressed(int key);		//Set de la tecla apretada
	void set_mousePos(unsigned int x, unsigned int y);	//Set posicion del mouse
	void set_mousePos(PositionVector mousePos);			//Set posicion del mouse
	void set_display(ALLEGRO_DISPLAY * display);		//Set display donde se dio el evento
	ALLEGRO_DISPLAY * get_display();					//Get display donde se dio el evento


private:
	PositionVector mousePos;	//Posicion del mouse
	ALLEGRO_DISPLAY * display;	//Display donde se dio el evento
	int keyPressed;				//Tecla apretada
};

