#include "circPosFactory.h"

circPosFactory::
circPosFactory(unsigned int nodeCount_, unsigned int centerX_, unsigned int centerY_, double radius_)
{
	nodeCount = nodeCount_;
	radius = radius_;
	centerX = centerX_;
	centerY = centerY_;
	currAngle = 0;

	if (nodeCount_ > 0)
	{
		angleStep = (MAX_ANGLE / nodeCount_);
	}
}

bool circPosFactory::
getNextPos(unsigned int& x, unsigned int& y)
{
	bool ret = false; // error por default

	if (nodeCount > 0)
	{
		x = (unsigned int) ( centerX + ( radius * cos(currAngle) ) ); // devuelvo coordenada x
		y = (unsigned int) ( centerY + ( radius * sin(currAngle) ) ); // devuelvo coordenada y
		currAngle += angleStep; // vector apuntando a la siguiente posición potencial del nodo
		nodeCount--; // decremento el contador de nodos
		ret = true; // devuelvo success
	}
	return ret;
}

circPosFactory::
~circPosFactory()
{
}
