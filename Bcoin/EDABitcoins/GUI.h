#include <allegro5/allegro.h>
#include <list>
#include "Controller.h"
#include "myGUIEventsData.h"

enum events{ALLEGRO_MOUSE_CLICKED, ALLEGRO_KEY_PRESSED, NO_EVENT};

using namespace std;

class GUI
{

public:
	GUI(void);
	~GUI(void);

	bool hasEvent();
	void parseEvent();
	void addNewGUIController(Controller * newController);
	void removeGUIController(Controller * controllerToRemove);

	bool ok(void);

private:
	list<Controller *> allControllers;
	ALLEGRO_EVENT rawEvent;
	ALLEGRO_EVENT_QUEUE * queue;
	int GUIEvent;
	myGUIEventsData GUIEventData;
	bool good;
};