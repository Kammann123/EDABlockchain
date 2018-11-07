#include "stdafx.h"
#include "Sec_Window_View.h"
#include "blockchain/cryptoeda.h"

#define DELETE(x) if( x ){ delete x; }

Sec_Window_View::
Sec_Window_View(FullService* node, PTPNetwork* network) {

	sendTransference = nullptr;
	sendMalTransference = nullptr;
	transferenceTo = nullptr;
	transferenceAmount = nullptr;

	sendTransferenceController = nullptr;
	sendMalTransferenceController = nullptr;
	transferenceToController = nullptr;
	transferenceAmountController = nullptr;

	to = nullptr;
	amount = nullptr;
	nodeIdTitle = nullptr;
	nodeIdText = nullptr;
	nodeStateTitle = nullptr;
	nodeStateText = nullptr;
	nodeTypeTitle = nullptr;
	nodeTypeText = nullptr;
	display = nullptr;

	this->node = node;
	this->network = network;
}

Sec_Window_View::
~Sec_Window_View(void) {

	this->hide();
}

void Sec_Window_View::
pop_up(void)
{
	sendTransference = new ALL_BUTTON(PositionVector(10, 10), PositionVector(200, 30), "Ejecutar transferencia", al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0));
	sendMalTransference = new ALL_BUTTON(PositionVector(10, 80), PositionVector(200, 30), "Ejecutar transferencia maliciosa", al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0));

	to = new Al_Label(PositionVector(270, 15), "Para: ", al_map_rgb(255, 255, 255), al_load_ttf_font("arial.ttf", 15, 0));
	transferenceTo = new EditText(PositionVector(300, 10), PositionVector(300, 30), "", al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), int_);

	amount = new Al_Label(PositionVector(260, 85), "Cantidad: ", al_map_rgb(255, 255, 255), al_load_ttf_font("arial.ttf", 15, 0));
	transferenceAmount = new EditText(PositionVector(300, 80), PositionVector(300, 30), "", al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), double_);

	sendTransferenceController = new ALL_BUTTON_CONTROLLER(sendTransference);
	sendMalTransferenceController = new ALL_BUTTON_CONTROLLER(sendMalTransference);
	transferenceToController = new EditText_Controller(transferenceTo);
	transferenceAmountController = new EditText_Controller(transferenceAmount);

	vector<byte> byteArray = cryptoeda::getByteArray(node->getPublicKey());
	nodeIdTitle = new Al_Label(PositionVector(100, 150), "Id del nodo: ", al_map_rgb(255, 255, 255), al_load_ttf_font("arial.ttf", 15, 0));
	nodeIdText = new Al_Label(PositionVector(200, 150), cryptoeda::getStringFromBytes(byteArray), al_map_rgb(255, 255, 255), al_load_ttf_font("arial.ttf", 15, 0));

	nodeTypeTitle = new Al_Label(PositionVector(100, 200), "Tipo de nodo: ", al_map_rgb(255, 255, 255), al_load_ttf_font("arial.ttf", 15, 0));
	nodeTypeText = new Al_Label(PositionVector(200, 200), (node->getType() == MINER_TYPE) ? "MINERO" : "FULL SERVICE", al_map_rgb(255, 255, 255), al_load_ttf_font("arial.ttf", 15, 0));

	this->node = node;
	string state;

	if ((node->getStatus()) == (IDLE))
		state = "ESPERANDO";
	else if ((node->getStatus()) == PENDING_MSG)
		state = "MENSAJE PENDIENTE";
	else
		state = "PROCESANDO MENSAJE";

	nodeStateTitle = new Al_Label(PositionVector(100, 250), "Estado del nodo: ", al_map_rgb(255, 255, 255), al_load_ttf_font("arial.ttf", 15, 0));
	nodeStateText = new Al_Label(PositionVector(200, 250), state, al_map_rgb(255, 255, 255), al_load_ttf_font("arial.ttf", 15, 0));


	this->display = display;
	sendTransference->to_display(display, display);
	sendMalTransference->to_display(display, display);
	transferenceTo->to_display(display, display);
	transferenceAmount->to_display(display, display);
	this->network = network;

	set_label_list();
	list<Al_Label *>::iterator it;
	for (it = labels.begin(); it != labels.end(); it++)
	{
		(*it)->show_label(display, display);
	}
}


void Sec_Window_View::
hide(void)
{
	DELETE(sendTransference);
	DELETE(sendMalTransference)
	DELETE(transferenceTo);
	DELETE(transferenceAmount);
	DELETE(sendTransferenceController);
	DELETE(sendMalTransferenceController);
	DELETE(transferenceToController);
	DELETE(transferenceAmountController);
	DELETE(nodeIdTitle);
	DELETE(nodeIdText);
	DELETE(nodeStateText);
	DELETE(nodeStateTitle);
	DELETE(nodeTypeText);
	DELETE(nodeTypeTitle);
	DELETE(to);
	DELETE(amount);

	al_destroy_display(display);
}

ALL_BUTTON_CONTROLLER * Sec_Window_View::get_sendTransfController()
{
	return sendTransferenceController;
}

ALL_BUTTON_CONTROLLER * Sec_Window_View::get_sendMalTransfController()
{
	return sendMalTransferenceController;
}
EditText_Controller * Sec_Window_View::get_transferenceToController()
{
	return transferenceToController;
}

EditText_Controller * Sec_Window_View::get_transferenceAmountController()
{
	return transferenceAmountController;
}

ALL_BUTTON * Sec_Window_View::get_sendTransference()
{
	return sendTransference;
}
ALL_BUTTON * Sec_Window_View::get_sendMalTransference()
{
	return sendMalTransference;
}

EditText * Sec_Window_View::get_transferenceTo()
{
	return transferenceTo;
}
EditText * Sec_Window_View::get_transferenceAmount()
{
	return transferenceAmount;
}

ALLEGRO_DISPLAY * Sec_Window_View::get_display()
{
	return display;
}

list<Al_Label*> * Sec_Window_View::get_labels()
{
	return &labels;
}

PTPNetwork * Sec_Window_View::get_network()
{
	return network;
}

FullService * Sec_Window_View::get_node()
{
	return node;
}

Al_Label * Sec_Window_View::get_nodeStateText()
{
	return nodeStateText;
}

Al_Label * Sec_Window_View::get_nodeTypeText()
{
	return nodeTypeText;
}

void Sec_Window_View::set_label_list()
{
	labels.push_back(to);
	labels.push_back(amount);
	labels.push_back(nodeIdTitle);
	labels.push_back(nodeIdText);
	labels.push_back(nodeStateTitle);
	labels.push_back(nodeStateText);
	labels.push_back(nodeTypeTitle);
	labels.push_back(nodeTypeText);
}

void Sec_Window_View::update()
{
	ALLEGRO_DISPLAY * display = windowModel->get_display();
	al_set_target_bitmap(al_get_backbuffer(display));
	al_clear_to_color(al_map_rgb(0, 0, 0));
	windowModel->get_sendTransference()->to_display(display, display);
	windowModel->get_sendMalTransference()->to_display(display, display);
	windowModel->get_transferenceAmount()->to_display(display, display);
	windowModel->get_transferenceTo()->to_display(display, display);
	list <Al_Label *> * labels = windowModel->get_labels();
	list<Al_Label *>::iterator it;
	for (it = labels->begin(); it != labels->end(); it++)
	{
		(*it)->show_label(display, display);
	}
}
