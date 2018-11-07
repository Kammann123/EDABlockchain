#pragma once
#include <iterator> 
#include "Subject.h"
#include <iostream> 
#include "window/ALL_BUTTON_CONTROLLER.h"
#include "window/EditText_Controller.h"
#include "FullService.h"
#include "window/Al_Label.h"
using namespace std;

class Sec_Window: public Subject
{
public:
	Sec_Window(ALLEGRO_DISPLAY * display, unsigned int nodeId, FullService * node, PTPNetwork * network);
	~Sec_Window();
	ALL_BUTTON_CONTROLLER * get_sendTransfController();
	ALL_BUTTON_CONTROLLER * get_sendMalTransfController();
	EditText_Controller * get_transferenceToController();
	EditText_Controller  * get_transferenceAmountController();

	ALL_BUTTON * get_sendTransference();
	ALL_BUTTON * get_sendMalTransference();
	EditText * get_transferenceTo();
	EditText * get_transferenceAmount();
	ALLEGRO_DISPLAY * get_display();
	list <Al_Label *> * get_labels();
	unsigned int get_nodeId();
	PTPNetwork * get_network();
	FullService * get_node();
	Al_Label * get_nodeStateText();
	Al_Label * get_nodeTypeText();

	void set_label_list();


private:
	ALL_BUTTON * sendTransference;
	ALL_BUTTON * sendMalTransference;
	EditText * transferenceTo;
	EditText * transferenceAmount;

	ALL_BUTTON_CONTROLLER * sendTransferenceController;
	ALL_BUTTON_CONTROLLER * sendMalTransferenceController;
	EditText_Controller * transferenceToController;
	EditText_Controller  * transferenceAmountController;

	Al_Label * to;
	Al_Label * amount;
	Al_Label * nodeIdTitle;
	Al_Label * nodeIdText;
	Al_Label * nodeStateTitle;
	Al_Label * nodeStateText;
	Al_Label * nodeTypeTitle;
	Al_Label * nodeTypeText;
	ALLEGRO_DISPLAY * display;

	list<Al_Label*> labels;

	FullService * node;
	PTPNetwork * network;

};

