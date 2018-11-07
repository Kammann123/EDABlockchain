#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "blockchain_actors/FullService.h"
#include "blockchain_actors/Miner.h"

#define FS_IDLE_COLOR (al_map_rgb(0,255,0)) // verde puro
#define FS_PENDING_MSG_COLOR  (al_map_rgb(0,153,51)) // verde mas oscuro
#define FS_PROCESS_MSG_COLOR  (al_map_rgb(102,255,102)) // verde oscuro

#define MINER_IDLE_COLOR (al_map_rgb(102,204,255)) // azul clar
#define MINER_MINING_COLOR (al_map_rgb(0,102,255)) // azul oscuro
#define MINER_SYNC_COLOR (al_map_rgb(0,0,204)) // verde mas oscuro

#define BACKGROUND_COLOR (al_map_rgb(0,0,0)) // negro

#define SELECTED_COLOR (al_map_rgb(255,255,255)) // blanco

#define SELECTED_RATIO 0.8 // número que indica el radio interior del anillo, respecto al radio exterior (Rext - Rint) = Ranillo, varía entre 0 y 1.

class Graphics
{
public:
	Graphics(unsigned int width, unsigned int height);
	~Graphics();

	/*
	* getDisplay
	*
	* Método getter que devuelve el puntero a display
	*/
	ALLEGRO_DISPLAY* getDisplay(void);
	unsigned int getWidth(void);
	unsigned int getHeight(void);

	/*
	* drawNode
	* 
	* Método que dibuja un nodo
	*/
	void drawNode(FullService& node);

private:
	ALLEGRO_DISPLAY* display; // main display
	unsigned int width;
	unsigned int height;

	//ALLEGRO_BITMAP* minerNode;  // bmap del nodo Miner
	//ALLEGRO_BITMAP* fullSNode; // bmap del nodo Full Service
	//ALLEGRO_BITMAP* nodeSelected; // bmap de selección de nodo
	bool allegroInit(unsigned int dw, unsigned int dh);
};