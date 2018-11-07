#include "../stdafx.h"
#include "EditText.h"

#include <algorithm>



EditText::EditText() 
{
}

EditText::EditText(PositionVector startPoint, int type) : Al_Component(startPoint)
{
	this->type = type;
}

EditText::EditText(PositionVector startPoint, PositionVector sizes, int type) : Al_Component(startPoint, sizes)
{
	this->type = type;
}

EditText::EditText(PositionVector startPoint, PositionVector sizes, string text, int type) : Al_Component(startPoint, sizes, text)
{
	this->type = type;
}

EditText::EditText(PositionVector startPoint, PositionVector sizes, string text, ALLEGRO_COLOR backColor, int type): Al_Component(startPoint, sizes, text, backColor)
{
	this->type = type;
}

EditText::EditText(PositionVector startPoint, PositionVector sizes, string text, ALLEGRO_COLOR backColor, ALLEGRO_COLOR textColor, int type): Al_Component(startPoint, sizes, text, backColor, textColor)
{
	this->type = type;
}

EditText::EditText(PositionVector startPoint, PositionVector sizes, string text, ALLEGRO_COLOR backColor, ALLEGRO_COLOR textColor, ALLEGRO_FONT * font, int type): Al_Component(startPoint, sizes, text, backColor, textColor, font)
{
	this->type = type;
}

EditText::~EditText()
{
}

bool EditText::get_focused()
{
	return focused;
}

void EditText::set_focused(bool a)
{
	focused = a;
}

void EditText::new_number(int c)
{
	string text = Al_Component::get_text();
	if (c != -1)
	{
		if(c!=-2)
			Al_Component::set_text(text + to_string(c));
		else
		{
			if (type == double_)
			{
				int count = 0;
				for (unsigned int i = 0; i < text.size(); i++)
					if (text[i] == '.')
						count++;
				if (!count)
					Al_Component::set_text(text + '.');
			}
		
		}
			
	}
	else 
	{
		if (text.size() >0)
			Al_Component::set_text(text.substr(0, text.size() - 1));
	}
	
	
}
