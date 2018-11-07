#include "../stdafx.h"
#include "Al_Component.h"
#include "iostream"

using namespace std;


Al_Component::Al_Component()
{
	text = DEFAULT_TEXT;
	sizes = PositionVector(DEFAULT_XSIZE, DEFAULT_YSIZE);
	startPoint = PositionVector(DEFAULT_XSTART, DEFAULT_YSTART);
	backColor = al_map_rgb(DEFAULT_BACK_COLOR);
	font = al_load_ttf_font(DEFAULT_FONT);
	textColor = al_map_rgb(DEFAULT_TEXT_COLOR);
}

Al_Component::Al_Component(PositionVector startPoint)
{
	this->startPoint = startPoint;
	text = DEFAULT_TEXT;
	sizes = PositionVector(DEFAULT_XSIZE, DEFAULT_YSIZE);
	backColor = al_map_rgb(DEFAULT_BACK_COLOR);
	textColor = al_map_rgb(DEFAULT_TEXT_COLOR);
	font = al_load_ttf_font(DEFAULT_FONT);
}

Al_Component::Al_Component(PositionVector startPoint, PositionVector sizes)
{
	this->sizes = sizes;
	text = DEFAULT_TEXT;
	this->startPoint = startPoint;
	backColor = al_map_rgb(DEFAULT_BACK_COLOR);
	font = al_load_ttf_font(DEFAULT_FONT);
	textColor = al_map_rgb(DEFAULT_TEXT_COLOR);
}

Al_Component::Al_Component(PositionVector startPoint, string text)
{
	sizes = PositionVector(DEFAULT_XSIZE, DEFAULT_YSIZE);
	this->startPoint = startPoint;
	this->text = text;
	textColor = al_map_rgb(DEFAULT_TEXT_COLOR);
	backColor = al_map_rgb(DEFAULT_BACK_COLOR);
	font = al_load_ttf_font(DEFAULT_FONT);
}

Al_Component::Al_Component(PositionVector startPoint, PositionVector sizes, string text)
{
	this->sizes = sizes;
	this->startPoint = startPoint;
	this->text = text;
	textColor = al_map_rgb(DEFAULT_TEXT_COLOR);
	backColor = al_map_rgb(DEFAULT_BACK_COLOR);
	font = al_load_ttf_font(DEFAULT_FONT);
}

Al_Component::Al_Component(PositionVector startPoint, string text, ALLEGRO_COLOR textColor)
{
	this->text = text;
	sizes = PositionVector(DEFAULT_XSIZE, DEFAULT_YSIZE);
	this->startPoint = startPoint;
	backColor = al_map_rgb(DEFAULT_BACK_COLOR);
	font = al_load_ttf_font(DEFAULT_FONT);
	this->textColor = textColor;
}

Al_Component::Al_Component(PositionVector startPoint, PositionVector sizes, string text, ALLEGRO_COLOR backColor)
{
	this->sizes = sizes;
	this->startPoint = startPoint;
	textColor = al_map_rgb(DEFAULT_TEXT_COLOR);
	this->text = text;
	font = al_load_ttf_font(DEFAULT_FONT);
	this->backColor = backColor;
}

Al_Component::Al_Component(PositionVector startPoint, string text, ALLEGRO_COLOR textColor, ALLEGRO_FONT * font)
{
	this->startPoint = startPoint;
	this->textColor = textColor;
	this->text = text;
	this->font = font;
	sizes = PositionVector(DEFAULT_XSIZE, DEFAULT_YSIZE);
	backColor = al_map_rgb(DEFAULT_BACK_COLOR);
}

Al_Component::Al_Component(PositionVector startPoint, PositionVector sizes, string text, ALLEGRO_COLOR backColor, ALLEGRO_COLOR textColor)
{
	this->sizes = sizes;
	this->startPoint = startPoint;
	this->textColor = textColor;
	this->text = text;
	font = al_load_ttf_font(DEFAULT_FONT);
	this->backColor = backColor;
}

Al_Component::Al_Component(PositionVector startPoint, PositionVector sizes, string text, ALLEGRO_COLOR backColor, ALLEGRO_COLOR textColor, ALLEGRO_FONT * font)
{
	this->sizes = sizes;
	this->startPoint = startPoint;
	this->textColor = textColor;
	this->text = text;
	this->font = font;
	this->backColor = backColor;
}

PositionVector Al_Component::get_start_point()
{
	return startPoint;
}

PositionVector Al_Component::get_sizes()
{
	return sizes;
}

string Al_Component::get_text()
{
	return text;
}


ALLEGRO_COLOR Al_Component::get_backColor()
{
	return backColor;
}

ALLEGRO_COLOR Al_Component::get_textColor()
{
	return textColor;
}

ALLEGRO_FONT * Al_Component::get_font()
{
	return font;
}

void Al_Component::set_text(string text)
{
	this->text = text;
}

void Al_Component::set_sizes(PositionVector sizes)
{
	this->sizes = sizes;
}

void Al_Component::set_startPoint(PositionVector startPoint)
{
	this->startPoint = startPoint;
}

void Al_Component::set_backColor(ALLEGRO_COLOR backColor)
{
	this->backColor = backColor;
}

void Al_Component::set_textColor(ALLEGRO_COLOR textColor)
{
	this->textColor = textColor;
}

void Al_Component::set_font(ALLEGRO_FONT * font)
{
	this->font = font;
}

bool Al_Component::isPointInsideRect(PositionVector position)
{
	unsigned int x = position.get_x();
	unsigned int y = position.get_y();

	if ((x >= startPoint.get_x()) && (x <= startPoint.get_x() + sizes.get_x()))
	{
		if ((y >= startPoint.get_y()) && (y <= startPoint.get_y() + sizes.get_y()))
		{
			return true;
		}
	}
	return false;
}



Al_Component::~Al_Component()
{
}


void Al_Component::to_display(ALLEGRO_DISPLAY * currentDisplay, ALLEGRO_DISPLAY * destDisplay)
{
	al_set_target_bitmap(al_get_backbuffer(destDisplay));
	al_draw_filled_rectangle(startPoint.get_x(), 
		startPoint.get_y(), 
		startPoint.get_x() + sizes.get_x(),
		startPoint.get_y() + sizes.get_y(),
		backColor);
	al_draw_text(font,
		textColor, 
		startPoint.get_x() + sizes.get_x() * PERC_MARGIN, 
		startPoint.get_y() + sizes.get_y() * PERC_MARGIN/2, 
		ALLEGRO_ALIGN_CENTRE,
		text.c_str());
	al_flip_display();
	al_set_target_bitmap(al_get_backbuffer(currentDisplay));
}

