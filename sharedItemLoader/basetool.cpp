#include "basetool.h"

BaseTool::BaseTool()
{
	setType(itemType::tool);
}

toolMode BaseTool::detectToolMode(QString mode)
{
	if (mode == "screwing") return toolMode::screwing;
	if (mode == "hammering") return toolMode::hammering;
	if (mode == "cutting") return toolMode::cutting;
	if (mode == "heating") return toolMode::heating;
	if (mode == "welding") return toolMode::welding;

	return toolMode::toolnomode;
}
