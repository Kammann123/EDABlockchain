#pragma once
#include <cmath>
#define MAX_ANGLE (2*(3.14159265359))

class circPosFactory
{
public:
	circPosFactory(unsigned int nodeCount_, unsigned int centerX_, unsigned int centerY_, double radius_);
	~circPosFactory();

	/*
	* getNextPos()
	*
	* Devuelve las coordenadas del siguiente nodo. true si hay exito, false si hay error
	*/
	bool getNextPos(unsigned int& x, unsigned int& y);

private:
	double angleStep;
	double currAngle;
	double radius;
	double centerX;
	double centerY;
	unsigned int nodeCount;
};