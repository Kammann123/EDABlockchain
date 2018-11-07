#pragma once
class PositionVector
{
public:
	PositionVector();
	PositionVector(unsigned int x, unsigned int y);
	~PositionVector();
	unsigned int get_x();
	unsigned int get_y();

	void set_x(unsigned int x);

	void set_y(unsigned int y);

private:
	unsigned int x;
	unsigned int y;
};

