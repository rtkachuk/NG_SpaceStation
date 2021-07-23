#include "baseitem.h"

BaseItem::BaseItem()
{
	m_name = "<NONAME>";
	m_description = "<NODESC>";
	m_id = "-1";
	m_mode = playerWearable::itemnomode;
	m_damage = 0;
	m_type = itemType::notype;
}

playerWearable BaseItem::detectPlayerWearable(QString mode)
{
	if (mode == "head") return playerWearable::head;
	if (mode == "torso")  return playerWearable::torso;
	if (mode == "legs")  return playerWearable::legs;
	if (mode == "foot")  return playerWearable::foot;
	if (mode == "holdable")  return playerWearable::holdable;
	if (mode == "gloves")  return playerWearable::gloves;

	return playerWearable::itemnomode;
}
