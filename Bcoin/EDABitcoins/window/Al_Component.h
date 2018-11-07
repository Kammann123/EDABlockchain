#pragma once
#include "../PositionVector.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <string>

using namespace std;

#define DEFAULT_XSTART		10
#define DEFAULT_YSTART		10
#define DEFAULT_TEXT		"BUTTON"
#define DEFAULT_XSIZE		50
#define DEFAULT_YSIZE		30
#define DEFAULT_BACK_COLOR	255,255,255
#define DEFAULT_FONT		"arial.ttf",10,0
#define DEFAULT_TEXT_COLOR	0,0,0
#define PERC_MARGIN			0.5

typedef void(*fptr)();
class Al_Component
{
public:
	Al_Component();
	Al_Component(PositionVector startPoint);
	Al_Component(PositionVector startPoint, PositionVector sizes);
	Al_Component(PositionVector startPoint, string text);
	Al_Component(PositionVector startPoint, PositionVector sizes, string text);
	Al_Component(PositionVector startPoint, string text,  ALLEGRO_COLOR textColor);
	Al_Component(PositionVector startPoint, PositionVector sizes, string text, ALLEGRO_COLOR backColor);
	Al_Component(PositionVector startPoint, string text, ALLEGRO_COLOR textColor, ALLEGRO_FONT* font);
	Al_Component(PositionVector startPoint, PositionVector sizes, string text, ALLEGRO_COLOR backColor, ALLEGRO_COLOR textColor);
	Al_Component(PositionVector startPoint, PositionVector sizes, string text, ALLEGRO_COLOR backColor, ALLEGRO_COLOR textColor, ALLEGRO_FONT* font);
	
	~Al_Component();

	PositionVector get_start_point();
	PositionVector get_sizes();
	string get_text();
	ALLEGRO_COLOR get_backColor();
	ALLEGRO_COLOR get_textColor();
	ALLEGRO_FONT* get_font();

	void set_text(string text);
	void set_sizes(PositionVector sizes);
	void set_startPoint(PositionVector startPoint);
	void set_backColor(ALLEGRO_COLOR backColor);
	void set_textColor(ALLEGRO_COLOR textColor);
	void set_font(ALLEGRO_FONT* font);
	bool isPointInsideRect(PositionVector position);

	void to_display(ALLEGRO_DISPLAY * currentDisplay, ALLEGRO_DISPLAY * destDisplay);

protected:
	PositionVector startPoint;
	PositionVector sizes;
	string text;
	ALLEGRO_COLOR backColor;
	ALLEGRO_COLOR textColor;
	ALLEGRO_FONT* font;
};

