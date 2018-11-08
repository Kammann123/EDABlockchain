#pragma once

#include <iterator>
#include <allegro5/allegro.h>
#include <iostream>

#include "PTPNetwork.h"
#include "Subject.h"
#include "window/ALL_BUTTON_CONTROLLER.h"
#include "window/EditText_Controller.h"
#include "blockchain_actors/FullService.h"
#include "window/Al_Label.h"

using namespace std;
/*Ventanas secundarias que aparecen al presionar sobre un nodo*/
class Sec_Window_View : public Observer
{
public:
	Sec_Window_View(FullService* node, PTPNetwork* network);	//Constructor
	~Sec_Window_View();	//Destructor
	void update();	//Update de la ventana

	/*Getters de los controllers de los componentes de la ventana*/
	ALL_BUTTON_CONTROLLER * get_sendTransfController();
	ALL_BUTTON_CONTROLLER * get_sendMalTransfController();
	EditText_Controller * get_transferenceToController();
	EditText_Controller  * get_transferenceAmountController();
	EditText_Controller  * get_feeAmountController();

	/*Getters de los componentes de la ventana*/
	ALL_BUTTON * get_sendTransference();
	ALL_BUTTON * get_sendMalTransference();
	EditText * get_transferenceTo();
	EditText * get_transferenceAmount();
	EditText * get_feeAmount();
	ALLEGRO_DISPLAY * get_display();
	list <Al_Label *> * get_labels();
	PTPNetwork * get_network();
	FullService * get_node();
	Al_Label * get_nodeStateText();
	Al_Label * get_nodeTypeText();

	void pop_up(void); //Se muestra la ventana
	void hide(void);	//Se esconde la ventana

private:

	/* Metodos privados! */
	void set_label_list(); //Se setea una lista con todos los labels que esten en la ventana

	/* Atributos de la clase */
	/*Botones y EditText*/
	ALL_BUTTON * sendTransference;
	ALL_BUTTON * sendMalTransference;
	EditText * transferenceTo;
	EditText * transferenceAmount;
	EditText * feeAmount;
	/*Contollers*/
	ALL_BUTTON_CONTROLLER * sendTransferenceController;
	ALL_BUTTON_CONTROLLER * sendMalTransferenceController;
	EditText_Controller * transferenceToController;
	EditText_Controller  * transferenceAmountController;
	EditText_Controller * feeAmountController;

	/*Labels y display*/
	Al_Label * to;
	Al_Label * amount;
	Al_Label * feeTitle;
	Al_Label * nodeIdTitle;
	Al_Label * nodeIdText;
	Al_Label * nodeStateTitle;
	Al_Label * nodeStateText;
	Al_Label * nodeTypeTitle;
	Al_Label * nodeTypeText;
	Al_Label * nodeBalanceTitle;
	Al_Label * nodeBalanceText;
	Al_Label * publicKeyTitle;
	Al_Label * publicKeyText;
	ALLEGRO_DISPLAY * display;
	list<Al_Label*> labels;

	FullService* node; //Nodo del cual depende
	PTPNetwork* network;	//Red en la cual se encuentra el nodo
};