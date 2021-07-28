#include "inventorycontroller.h"

InventoryController::InventoryController(ItemLoader *loader)
{
	m_itemLoader = loader;
}

QByteArray InventoryController::wearId(QByteArray id, playerWearable place, QTcpSocket *player)
{
	if (m_inventories[player].contains(id))
		return m_wear[player].wearOn(id, place);
	return "";
}
