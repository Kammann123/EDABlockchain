#include "../stdafx.h"
#include "ALL_BUTTON.h"



ALL_BUTTON::ALL_BUTTON()
{
}

ALL_BUTTON::ALL_BUTTON(PositionVector startPoint) : Al_Component(startPoint)
{
}

ALL_BUTTON::ALL_BUTTON(PositionVector startPoint, PositionVector sizes) : Al_Component(startPoint, sizes)
{

}

ALL_BUTTON::ALL_BUTTON(PositionVector startPoint, PositionVector sizes, string text) : Al_Component(startPoint, sizes, text)
{

}

ALL_BUTTON::ALL_BUTTON(PositionVector startPoint, PositionVector sizes, string text, ALLEGRO_COLOR backColor) : Al_Component(startPoint, sizes, text, backColor)
{

}

ALL_BUTTON::ALL_BUTTON(PositionVector startPoint, PositionVector sizes, string text, ALLEGRO_COLOR backColor, ALLEGRO_COLOR textColor) : Al_Component(startPoint, sizes, text, backColor, textColor)
{
}

ALL_BUTTON::ALL_BUTTON(PositionVector startPoint, PositionVector sizes, string text, ALLEGRO_COLOR backColor, ALLEGRO_COLOR textColor, ALLEGRO_FONT * font) : Al_Component(startPoint, sizes, text, backColor, textColor, font)
{

}

ALL_BUTTON::~ALL_BUTTON()
{
}

bool ALL_BUTTON::get_action_flag()
{
	return doActionFlag;
}

void ALL_BUTTON::set_action_flag(bool flag)
{
	doActionFlag = flag;
}


