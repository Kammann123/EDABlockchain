#include "stdafx.h"
#include "GUI.h"
#include <sstream>
#include "iostream"
#include "Sec_Window_Controller.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

using namespace std;

bool GUI::
ok(void) {

	return good;
}

GUI::GUI(void)
{
	good = true;

	queue = al_create_event_queue();
	if (queue) {

		if (al_install_keyboard()) {

			if (al_install_mouse()) {

				if (al_init_primitives_addon()) {

					al_init_font_addon(); // initialize the font addon
					al_init_ttf_addon();// initialize the ttf (True Type Font) addon

					al_register_event_source(queue, al_get_keyboard_event_source());
					al_register_event_source(queue, al_get_mouse_event_source());
				}
			}
		}
	}

	good = false;
}

GUI::~GUI(void) {

	if(queue)
		al_destroy_event_queue(queue);
}

bool
GUI::hasEvent()
{
	string b, c, aPad, aCompare;
	if (al_get_next_event(queue, &rawEvent))
	{
		switch (rawEvent.type)
		{
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			GUIEvent = ALLEGRO_MOUSE_CLICKED;
			GUIEventData.set_display(rawEvent.mouse.display);
			GUIEventData.set_mousePos(rawEvent.mouse.x, rawEvent.mouse.y);
			return true;
			break;

		case ALLEGRO_EVENT_KEY_DOWN:
			GUIEvent = NO_EVENT;
			const char *a = al_keycode_to_name(rawEvent.keyboard.keycode);
			int num = atoi(a);
			aCompare=a;
			b = "BACKSPACE";
			c = "KEY73";
			if (aCompare == b)
			{
				GUIEvent = ALLEGRO_KEY_PRESSED;
				GUIEventData.set_keyPressed(-1);
				return true;
			}
			else if (aCompare == "0")
			{
				GUIEvent = ALLEGRO_KEY_PRESSED;
				GUIEventData.set_keyPressed(0);
				return true;
			}
			else if ((num <= 9) && (num > 0))
			{
				GUIEvent = ALLEGRO_KEY_PRESSED;
				GUIEventData.set_keyPressed(num);
				return true;
			}
			else if (aCompare == c)
			{
				GUIEvent = ALLEGRO_KEY_PRESSED;
				GUIEventData.set_keyPressed(-2);
				return true;
			}
			else
			{
				aPad = aCompare.substr(0, aCompare.size() - 1);
				if (aPad == "PAD ")
				{
					string number = aCompare.substr(aCompare.size() - 1, 2);
					num = atoi(number.c_str());
					if ((num > 0) || (number == "0"))
					{
						GUIEvent = ALLEGRO_KEY_PRESSED;
						GUIEventData.set_keyPressed(num);
						return true;
					}

				}
			}
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			GUIEvent = ALLEGRO_DISPLAY_CLOSED;
			GUIEventData.set_display(rawEvent.display.source);
			return true;
			break;
		}
		return false;

	}
}

void
GUI::parseEvent()
{
	list<Controller *>::iterator it;
	for (it = allControllers.begin(); it != allControllers.end(); it++)
	{
		switch (GUIEvent)
		{
		case ALLEGRO_MOUSE_CLICKED:
			(*it)->parseMouseEvent(&GUIEventData);
			break;
		case ALLEGRO_KEY_PRESSED:
			(*it)->parseKeyboardEvent(&GUIEventData);
			break;
		case ALLEGRO_DISPLAY_CLOSED:
			(*it)->parseCloseEvent(&GUIEventData);
			break;
		default:
			//Unkonwn Event. Dependiendo del programa esto puede ser un error.
			//Lo que pongan acá va a depender del error handling que hagan.
			break;
		}
	}

}

void GUI::addNewGUIController(Controller * newController)
{
	allControllers.push_back(newController);
}

void GUI::removeGUIController(Controller * controllerToRemove)
{
	allControllers.remove(controllerToRemove);
}

bool GUI::exit(ALLEGRO_DISPLAY * mainDisplay)
{
	if ((GUIEvent == ALLEGRO_DISPLAY_CLOSED) && (GUIEventData.get_display() == mainDisplay))
		return true;
	return false;
}
