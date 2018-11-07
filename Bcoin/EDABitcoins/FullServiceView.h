#pragma once
#include "blockchain_actors/FullService.h"
#include "Observer.h"
#include "Graphics.h"

class FullServiceView : public Observer
{
public:
	FullServiceView(FullService& node_, Graphics& graphics_);
	~FullServiceView();
	void update(void);
private:
	FullService& node;
	Graphics& graphics;
};