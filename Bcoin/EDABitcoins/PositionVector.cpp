#include "stdafx.h"
#include "PositionVector.h"


PositionVector::PositionVector()
{
}

PositionVector::PositionVector(unsigned int x, unsigned int y)
{
	this->x = x;
	this->y = y;
}

PositionVector::~PositionVector()
{
}

unsigned int PositionVector::get_x()
{
	return x;
}

unsigned int PositionVector::get_y()
{
	return y;
}

void PositionVector::set_x(unsigned int x)
{
	this->x = x;
}

void PositionVector::set_y(unsigned int y)
{
	this->y = y;
}
