#include "../stdafx.h"
#include "Al_Label.h"


Al_Label::Al_Label(PositionVector startPoint, string initialText) : Al_Component(startPoint, initialText)
{
}


Al_Label::Al_Label(PositionVector startPoint, string initialText, ALLEGRO_COLOR textColor): Al_Component(startPoint, initialText, textColor)
{
}

Al_Label::Al_Label(PositionVector startPoint, string initialText, ALLEGRO_COLOR textColor, ALLEGRO_FONT * font): Al_Component(startPoint, initialText, textColor, font)
{
}

Al_Label::~Al_Label()
{
}

void Al_Label::show_label(ALLEGRO_DISPLAY * currentDisplay, ALLEGRO_DISPLAY * destDisplay)
{

	al_set_target_bitmap(al_get_backbuffer(destDisplay));
	al_draw_text(font,
		textColor,
		startPoint.get_x(),
		startPoint.get_y(),
		ALLEGRO_ALIGN_CENTRE,
		text.c_str());
	al_flip_display();
	al_set_target_bitmap(al_get_backbuffer(currentDisplay));


}
