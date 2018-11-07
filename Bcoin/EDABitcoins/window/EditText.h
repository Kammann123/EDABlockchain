#pragma once
#include "Al_Component.h"
enum types {int_, double_};

using namespace std;
class EditText: public Al_Component
{
public:
	EditText();
	EditText(PositionVector startPoint, int type);
	EditText(PositionVector startPoint, PositionVector sizes, int type);
	EditText(PositionVector startPoint, PositionVector sizes, string initialText, int type);
	EditText(PositionVector startPoint, PositionVector sizes, string initialText, ALLEGRO_COLOR backColor, int type);
	EditText(PositionVector startPoint, PositionVector sizes, string initialText, ALLEGRO_COLOR backColor, ALLEGRO_COLOR textColor, int type);
	EditText(PositionVector startPoint, PositionVector sizes, string initialText, ALLEGRO_COLOR backColor, ALLEGRO_COLOR textColor, ALLEGRO_FONT* font, int type);
	~EditText();
	bool get_focused();
	void set_focused(bool a);
	void new_number(int c);
private:
	bool focused;
	int type;
};

