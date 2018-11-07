#pragma once
#include "Observer.h"
#include "blockchain_network/BlockchainNode.h"
#include "blockchain_actors/FullService.h"
#include "PTPNetwork.h"
#include <map>
#include <vector>

#define LINE_THICKNESS 2.0
#define LINE_COLOR (al_map_rgb(255,255,255)) // blanco

class PTPNetworkView : public Observer
{
public:
	PTPNetworkView(PTPNetwork& network_);
	~PTPNetworkView();
	void update(void);

private:
	PTPNetwork& network;
};

