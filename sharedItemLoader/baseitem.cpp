#include "baseitem.h"

BaseItem::BaseItem()
{
	m_name = "<NONAME>";
	m_description = "<NODESC>";
	m_id = "-1";
	m_wMode = playerWearable::itemnomode;
	m_tMode = toolMode::toolnomode;
	m_weapMode = weaponMode::noweaponmode;
	m_damage = 0;
	m_type = itemType::notype;
	m_pixmap = "/items/noitem.png";
}

playerWearable BaseItem::detectPlayerWearable(QString mode)
{
	if (mode == "head") return playerWearable::head;
	if (mode == "torso")  return playerWearable::torso;
	if (mode == "legs")  return playerWearable::legs;
	if (mode == "feet")  return playerWearable::feet;
	if (mode == "holdable")  return playerWearable::holdable;
	if (mode == "gloves")  return playerWearable::gloves;

	return playerWearable::itemnomode;
}

toolMode BaseItem::detectToolMode(QString mode)
{
	if (mode == "screwing") return toolMode::screwing;
	if (mode == "hammering") return toolMode::hammering;
	if (mode == "cutting") return toolMode::cutting;
	if (mode == "heating") return toolMode::heating;
	if (mode == "welding") return toolMode::welding;
	if (mode == "wrenching") return toolMode::wrenching;

	return toolMode::toolnomode;
}

weaponMode BaseItem::detectWeaponMode(QString mode)
{
	if (mode == "melee") return weaponMode::melee;
	if (mode == "longRange") return weaponMode::longRange;
	return weaponMode::noweaponmode;
}
