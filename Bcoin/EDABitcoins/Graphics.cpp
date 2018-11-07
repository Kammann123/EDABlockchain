#include "Graphics.h"

Graphics::Graphics(unsigned int width, unsigned int height)
{
	/* Guardo los parametros */
	this->width = width;
	this->height = height;

	/* Inicializo allegro */
	allegroInit(width, height);
}

Graphics::~Graphics()
{
}

ALLEGRO_DISPLAY * Graphics::
getDisplay(void)
{

	return display;
}

void Graphics::
drawNode(FullService& node)
{
	float Nradius = (float) node.get_radius(); // radio de dibujado

	if (node.isSelected()) // si el nodo está seleccionado, dibujo el radio interior
	{
		al_draw_filled_circle(node.get_posx(), node.get_posy(), Nradius, SELECTED_COLOR);
		Nradius *= SELECTED_RATIO; // ajusto el radio de dibujado
	}

	if (node.getType() == FULLSERVICE_TYPE) // si el nodo es FullService
	{

		switch ( (FullService::Status)node.getStatus() )
		{
			case FullService::Status::IDLE :
				al_draw_filled_circle(node.get_posx(), node.get_posy(), Nradius, FS_IDLE_COLOR);
				break;

			case FullService::Status::PENDING_MSG :
				al_draw_filled_circle(node.get_posx(), node.get_posy(), Nradius, FS_PENDING_MSG_COLOR);
				break;

			case FullService::Status::PROCESS_MSG :
				al_draw_filled_circle(node.get_posx(), node.get_posy(), Nradius, FS_PROCESS_MSG_COLOR);
				break;
		}
	}

	else // si el nodo es Miner
	{
		switch ( (Miner::Status)node.getStatus() )
		{
			case Miner::Status::IDLE :
				al_draw_filled_circle(node.get_posx(), node.get_posy(), Nradius, MINER_IDLE_COLOR);
				break;

			case Miner::Status::MINING :
				al_draw_filled_circle(node.get_posx(), node.get_posy(), Nradius, MINER_MINING_COLOR);
				break;

			case Miner::Status::SYNC :
				al_draw_filled_circle(node.get_posx(), node.get_posy(), Nradius, MINER_SYNC_COLOR);
				break;
		}
	}

	al_flip_display(); // mirror de los cambios
}

bool Graphics::
allegroInit(unsigned int dw, unsigned int dh)
{
	bool error_flag = false, init = true;

	if (!(al_is_system_installed())) // si no está previamente inicializado, inicializo Allegro
	{
		init = al_init();
	}

	if (!al_init())
	{
		error_flag = true;
	}

	else if (!init || (!(display = al_create_display(dw, dh))) )
	{
		error_flag = true;
	}

	else if ( !init || (!(al_init_primitives_addon())) )
	{
		error_flag = true;
		al_destroy_display(display);
	}

	
	return error_flag;
}

unsigned int Graphics::
getWidth(void) {

	return width;
}

unsigned int Graphics::
getHeight(void) {

	return height;
}