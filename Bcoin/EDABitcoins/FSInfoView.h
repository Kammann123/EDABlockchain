#pragma once
#include "Observer.h"
#include "blockchain_actors/FullService.h"
#include"PTPNetwork.h"

class FSInfoView : public Observer
{
public:
	FSInfoView(FullService& node_, idk& windowManager_, PTPNetwork& network_ );
	~FSInfoView();
	void update(void);

private:
	FullService& node;
	PTPNetwork& network;
	idk& windowManager;
};

