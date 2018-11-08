#include <allegro5/allegro.h>
#include <list>
#include "Controller.h"
#include "myGUIEventsData.h"

enum events{ALLEGRO_MOUSE_CLICKED, ALLEGRO_KEY_PRESSED, NO_EVENT, ALLEGRO_DISPLAY_CLOSED};

using namespace std;

class GUI
{

public:
	GUI(void);
	~GUI(void);

	bool hasEvent();		//Devuelve si se encontro algun evento
	void parseEvent();		//Parsea el evento
	void addNewGUIController(Controller * newController);	//Se le anaden controladores
	void removeGUIController(Controller * controllerToRemove);	//Se le sacan controladores
	bool exit(ALLEGRO_DISPLAY * mainDisplay);

	bool ok(void);

private:
	list<Controller *> allControllers;	//Lista de controladores
	ALLEGRO_EVENT rawEvent;				//Evento de allegro recibido
	ALLEGRO_EVENT_QUEUE * queue;		//Cola de eventos de allegro
	int GUIEvent;						//Tipo de evento
	myGUIEventsData GUIEventData;		//Informacion del evento
	bool good;
};