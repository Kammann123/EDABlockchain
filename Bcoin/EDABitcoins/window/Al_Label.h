#pragma once
#include "Al_Component.h"
using namespace std;
class Al_Label : public Al_Component
{
public:
	Al_Label(PositionVector startPoint, string initialText);
	Al_Label(PositionVector startPoint, string initialText, ALLEGRO_COLOR textColor);
	Al_Label(PositionVector startPoint, string initialText, ALLEGRO_COLOR textColor, ALLEGRO_FONT* font);
	~Al_Label();
	void show_label(ALLEGRO_DISPLAY * currentDisplay, ALLEGRO_DISPLAY * destDisplay);

};

