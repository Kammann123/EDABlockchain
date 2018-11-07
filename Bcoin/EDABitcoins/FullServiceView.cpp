#include "FullServiceView.h"

FullServiceView::FullServiceView(FullService& node_, Graphics& graphics_):node(node_),graphics(graphics_)
{
}

FullServiceView::~FullServiceView()
{
}

void FullServiceView::
update(void)
{
	graphics.drawNode(node); // dibujo el nodo
}
