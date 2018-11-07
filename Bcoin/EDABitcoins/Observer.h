#pragma once

/*
* Observer
* Clase abstracta de un Observer para la implementacion de MVC
*/
class Observer {

public:

	/*
	* Constructores y destructores
	*/
	Observer(void);
	virtual ~Observer(void);

	/*
	* update
	* La implementacion del update es llamada cuando los modelos
	* realizan una notificacion de todos los observers.
	*/
	virtual void update(void) = 0;
};