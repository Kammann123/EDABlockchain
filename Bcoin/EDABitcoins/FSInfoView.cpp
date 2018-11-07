#include "FSInfoView.h"



FSInfoView::FSInfoView(FullService& node_, idk& windowManager_,PTPNetwork& network_):node(node_),windowManager(windowManager_), network(network_)
{
}


FSInfoView::~FSInfoView()
{
}

void FSInfoView::update(void)
{
	if (node.isSelected() && !windowManager.isWindowOpen()) // ventana cerrada y nodo seleccionado -> crear ventana
	{
		windowManager.openWindow(node, network);
	}

	else if(!node.isSelected() && windowManager.isWindowOpen()) // nodo no seleccionado y ventana abierta -> cerrar ventana
	{
		windowManager.closeWindow();
	}

	else if (node.isSelected() && windowManager.isWindowOpen()) // nodo seleccionado y ventana abierta -> update del estado
	{
		windowManager.updateInfo();
	}
}
