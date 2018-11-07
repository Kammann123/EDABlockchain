#include "stdafx.h"
#include "Sec_Window.h"


Sec_Window::Sec_Window(ALLEGRO_DISPLAY * display, unsigned int nodeId, FullService * node, PTPNetwork * network)
{
	sendTransference = new ALL_BUTTON(PositionVector(10, 10) , PositionVector(200, 30), "Ejecutar transferencia", al_map_rgb(255,255,255), al_map_rgb(0, 0, 0));
	sendMalTransference = new ALL_BUTTON(PositionVector(10, 80), PositionVector(200, 30), "Ejecutar transferencia maliciosa", al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0));

	to = new Al_Label(PositionVector(270, 15), "Para: ", al_map_rgb(255, 255, 255), al_load_ttf_font("arial.ttf", 15, 0));
	transferenceTo = new EditText(PositionVector(300, 10), PositionVector(300, 30), "", al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), int_);

	amount = new Al_Label(PositionVector(260, 85), "Cantidad: ", al_map_rgb(255, 255, 255), al_load_ttf_font("arial.ttf", 15, 0));
	transferenceAmount= new EditText(PositionVector(300, 80), PositionVector(300, 30), "", al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), double_);

	sendTransferenceController = new ALL_BUTTON_CONTROLLER(sendTransference);
	sendMalTransferenceController = new ALL_BUTTON_CONTROLLER(sendMalTransference);
	transferenceToController = new EditText_Controller(transferenceTo);
	transferenceAmountController = new EditText_Controller(transferenceAmount);

	nodeIdTitle = new Al_Label(PositionVector(100, 150), "Id del nodo: ", al_map_rgb(255, 255, 255), al_load_ttf_font("arial.ttf", 15, 0));
	nodeIdText = new Al_Label(PositionVector(200, 150), to_string(nodeId), al_map_rgb(255, 255, 255), al_load_ttf_font("arial.ttf", 15, 0));

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


	this->nodeId = nodeId;
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


Sec_Window::~Sec_Window()
{
	delete sendTransference;
	delete sendMalTransference;
	delete transferenceTo;
	delete transferenceAmount;
	delete sendTransferenceController;
	delete sendMalTransferenceController;
	delete transferenceToController;
	delete transferenceAmountController;
	delete nodeIdTitle;
	delete nodeIdText;
	delete nodeStateText;
	delete nodeStateTitle;
	delete nodeTypeText;
	delete nodeTypeTitle;
	delete to;
	delete amount;
	al_destroy_display(display);
}

ALL_BUTTON_CONTROLLER * Sec_Window::get_sendTransfController()
{
	return sendTransferenceController;
}

ALL_BUTTON_CONTROLLER * Sec_Window::get_sendMalTransfController()
{
	return sendMalTransferenceController;
}
EditText_Controller * Sec_Window::get_transferenceToController()
{
	return transferenceToController;
}

EditText_Controller * Sec_Window::get_transferenceAmountController()
{
	return transferenceAmountController;
}

ALL_BUTTON * Sec_Window::get_sendTransference()
{
	return sendTransference;
}
ALL_BUTTON * Sec_Window::get_sendMalTransference()
{
	return sendMalTransference;
}

EditText * Sec_Window::get_transferenceTo()
{
	return transferenceTo;
}
EditText * Sec_Window::get_transferenceAmount()
{
	return transferenceAmount;
}

ALLEGRO_DISPLAY * Sec_Window::get_display()
{
	return display;
}

list<Al_Label*> * Sec_Window::get_labels()
{
	return &labels;
}

unsigned int Sec_Window::get_nodeId()
{
	return nodeId;
}

PTPNetwork * Sec_Window::get_network()
{
	return network;
}

FullService * Sec_Window::get_node()
{
	return node;
}

Al_Label * Sec_Window::get_nodeStateText()
{
	return nodeStateText;
}

Al_Label * Sec_Window::get_nodeTypeText()
{
	return nodeTypeText;
}

void Sec_Window::set_label_list()
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


