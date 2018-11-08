#pragma once
class PositionVector
{
	//Vector con coordenadas x e y
public:
	/*Constructores*/
	PositionVector();
	PositionVector(unsigned int x, unsigned int y);
	/*Destructor*/
	~PositionVector();
	/*Getters*/
	unsigned int get_x();
	unsigned int get_y();
	/*Seters*/
	void set_x(unsigned int x);

	void set_y(unsigned int y);

private:
	/*Variables miembro*/
	unsigned int x;
	unsigned int y;
};

