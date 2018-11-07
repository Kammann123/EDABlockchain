#pragma once
#include "Al_Component.h"

using namespace std;

class ALL_BUTTON: public Al_Component
{
public:
	ALL_BUTTON();
	ALL_BUTTON(PositionVector startPoint);
	ALL_BUTTON(PositionVector startPoint, PositionVector sizes);
	ALL_BUTTON(PositionVector startPoint, PositionVector sizes, string text);
	ALL_BUTTON(PositionVector startPoint, PositionVector sizes, string text, ALLEGRO_COLOR backColor);
	ALL_BUTTON(PositionVector startPoint, PositionVector sizes, string text, ALLEGRO_COLOR backColor, ALLEGRO_COLOR textColor);
	ALL_BUTTON(PositionVector startPoint, PositionVector sizes, string text, ALLEGRO_COLOR backColor, ALLEGRO_COLOR textColor, ALLEGRO_FONT* font);
	~ALL_BUTTON();
	bool get_action_flag();
	void set_action_flag(bool flag);
private:
	bool doActionFlag;

};

