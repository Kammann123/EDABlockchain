#pragma once 

#include "Observer.h"

#include <list>

using namespace std;

/*
* Subject
* Clase abstracta que defije un sujeto, de quien heredan los modelos para tener
* observers y notificar cambios de estado de los mismos modelso.
*/
class Subject {

public:

	/*
	* Constructores y destructores
	*/
	Subject(void);
	virtual ~Subject(void);

	/*
	* attach
	* Agrega observers al sujeto
	*/
	bool attach(Observer* ptr);
	
	/*
	* detach
	* Remueve un observer del sujeto
	*/
	bool detach(Observer* ptr);

protected:

	/*
	* notifyObservers
	* Notifica a todos los observers de un cambio
	* ejecutando los metodos update() de cada uno.
	*/
	void notifyObservers(void);

private:
	list<Observer*> observers;
};