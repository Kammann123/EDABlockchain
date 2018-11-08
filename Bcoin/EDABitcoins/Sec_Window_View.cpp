#include "stdafx.h"
#include "Sec_Window_View.h"
#include "blockchain/cryptoeda.h"
#include "window/EditText_Controller.h"
#include "window/ALL_BUTTON_CONTROLLER.h"

#define DELETE(x) if( x ){ delete x, x = nullptr; }

Sec_Window_View::
Sec_Window_View(FullService* node, PTPNetwork* network) {

	sendTransference = nullptr;
	sendMalTransference = nullptr;
	transferenceTo = nullptr;
	transferenceAmount = nullptr;
	feeAmount = nullptr;

	sendTransferenceController = nullptr;
	sendMalTransferenceController = nullptr;
	transferenceToController = nullptr;
	transferenceAmountController = nullptr;
	feeAmountController = nullptr;

	feeTitle = nullptr;
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

	vector<byte> byteArray = cryptoeda::getByteArray(node->getPublicKey());
	string publicKey = cryptoeda::getStringFromBytes(byteArray);

	double balance = node->balance(node->getPublicKey());

	display = al_create_display(640, 480);

	/*Se crean todos los componentes de la ventana*/
	sendTransference = new ALL_BUTTON(PositionVector(10, 10), PositionVector(200, 30), "Ejecutar transferencia", al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0));
	sendMalTransference = new ALL_BUTTON(PositionVector(10, 80), PositionVector(200, 30), "Ejecutar transferencia maliciosa", al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0));

	to = new Al_Label(PositionVector(270, 15), "Para: ", al_map_rgb(255, 255, 255), al_load_ttf_font("arial.ttf", 15, 0));
	transferenceTo = new EditText(PositionVector(300, 10), PositionVector(300, 30), "", al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), int_);

	amount = new Al_Label(PositionVector(260, 85), "Cantidad: ", al_map_rgb(255, 255, 255), al_load_ttf_font("arial.ttf", 15, 0));
	transferenceAmount = new EditText(PositionVector(300, 80), PositionVector(300, 30), "", al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), double_);

	feeTitle = new Al_Label(PositionVector(260, 155), "Fee: ", al_map_rgb(255, 255, 255), al_load_ttf_font("arial.ttf", 15, 0));
	feeAmount = new EditText(PositionVector(300, 150), PositionVector(300, 30), "0", al_map_rgb(255, 255, 255), al_map_rgb(0, 0, 0), double_);

	/*Se asocian las vistas con los controllers*/
	sendTransferenceController = new ALL_BUTTON_CONTROLLER(sendTransference);
	sendMalTransferenceController = new ALL_BUTTON_CONTROLLER(sendMalTransference);
	transferenceToController = new EditText_Controller(transferenceTo);
	transferenceAmountController = new EditText_Controller(transferenceAmount);
	feeAmountController = new EditText_Controller(feeAmount);

	nodeIdTitle = new Al_Label(PositionVector(100, 200), "Id del nodo: ", al_map_rgb(255, 255, 255), al_load_ttf_font("arial.ttf", 15, 0));
	nodeIdText = new Al_Label(PositionVector(300, 200), to_string(network->getNodeId(node)), al_map_rgb(255, 255, 255), al_load_ttf_font("arial.ttf", 15, 0));

	nodeTypeTitle = new Al_Label(PositionVector(100, 240), "Tipo de nodo: ", al_map_rgb(255, 255, 255), al_load_ttf_font("arial.ttf", 15, 0));
	nodeTypeText = new Al_Label(PositionVector(300, 240), (node->getType() == MINER_TYPE) ? "MINERO" : "FULL SERVICE", al_map_rgb(255, 255, 255), al_load_ttf_font("arial.ttf", 15, 0));

	publicKeyTitle = new Al_Label(PositionVector(100, 280), "Public key del nodo: ", al_map_rgb(255, 255, 255), al_load_ttf_font("arial.ttf", 15, 0));
	publicKeyText = new Al_Label(PositionVector(300, 280), publicKey, al_map_rgb(255, 255, 255), al_load_ttf_font("arial.ttf", 15, 0));

	nodeBalanceTitle = new Al_Label(PositionVector(100, 320), "Balance de; nodo: ", al_map_rgb(255, 255, 255), al_load_ttf_font("arial.ttf", 15, 0));
	nodeBalanceText = new Al_Label(PositionVector(300, 320), to_string(balance), al_map_rgb(255, 255, 255), al_load_ttf_font("arial.ttf", 15, 0));

	this->node = node;
	string state;

	/*String a mostrar depende del estado*/
	if (((FullService::Status)node->getStatus()) == (FullService::Status::IDLE))
		state = "ESPERANDO";
	else if (((FullService::Status)node->getStatus()) == FullService::Status::PENDING_MSG)
		state = "MENSAJE PENDIENTE";
	else
		state = "PROCESANDO MENSAJE";

	nodeStateTitle = new Al_Label(PositionVector(100, 360), "Estado del nodo: ", al_map_rgb(255, 255, 255), al_load_ttf_font("arial.ttf", 15, 0));
	nodeStateText = new Al_Label(PositionVector(300, 360), state, al_map_rgb(255, 255, 255), al_load_ttf_font("arial.ttf", 15, 0));

	/*Muestro componentes*/

	this->display = display;
	sendTransference->to_display(display, display);
	sendMalTransference->to_display(display, display);
	transferenceTo->to_display(display, display);
	transferenceAmount->to_display(display, display);
	feeAmount->to_display(display, display);
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
	/*Se borran todos los componentes*/
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
	DELETE(nodeBalanceTitle);
	DELETE(nodeBalanceText);
	DELETE(publicKeyText);
	DELETE(publicKeyTitle);
	DELETE(to);
	DELETE(amount);
	DELETE(feeTitle);
	DELETE(feeAmount);
	DELETE(feeAmountController);

	al_destroy_display(display);
	display = nullptr;
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

EditText_Controller * Sec_Window_View::get_feeAmountController()
{
	return feeAmountController;
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

EditText * Sec_Window_View::get_feeAmount()
{
	return feeAmount;
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
	/*Se agregan los labels a la lista*/
	labels.push_back(to);
	labels.push_back(amount);
	labels.push_back(nodeIdTitle);
	labels.push_back(nodeIdText);
	labels.push_back(nodeStateTitle);
	labels.push_back(nodeStateText);
	labels.push_back(nodeTypeTitle);
	labels.push_back(nodeTypeText);
	labels.push_back(publicKeyTitle);
	labels.push_back(publicKeyText);
	labels.push_back(nodeBalanceTitle);
	labels.push_back(nodeBalanceText);
	labels.push_back(feeTitle);
}

void Sec_Window_View::update()
{
	if (node->isSelected()) {

		if (this->display) {	//Existe display?

			string type, state;
			/*String a mostrar depende de tipo y de estado*/
			(node->getType() == MINER_TYPE) ? type = "MINERO" : type = "FULL SERVICE";
			if (((FullService::Status)node->getStatus()) == (FullService::Status::IDLE))
				state = "ESPERANDO";
			else if (((FullService::Status)node->getStatus()) == FullService::Status::PENDING_MSG)
				state = "MENSAJE PENDIENTE";
			else
				state = "PROCESANDO MENSAJE";
			get_nodeTypeText()->set_text(type);
			get_nodeStateText()->set_text(state);

			/*Se muestran los componentes*/
			al_set_target_bitmap(al_get_backbuffer(display));
			al_clear_to_color(al_map_rgb(0, 0, 0));
			get_sendTransference()->to_display(display, display);
			get_sendMalTransference()->to_display(display, display);
			get_transferenceAmount()->to_display(display, display);
			get_transferenceTo()->to_display(display, display);
			get_feeAmount()->to_display(display, display);
			list <Al_Label *> * labels = get_labels();
			list<Al_Label *>::iterator it;
			for (it = labels->begin(); it != labels->end(); it++)
			{
				(*it)->show_label(display, display);
			}
		}
		else {

			this->pop_up();	//Se muestra el display
		}
	}
	else {

		if (this->display) {

			this->hide();	//Se esconde el display
		}
	}
}
