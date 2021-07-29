#include "inventorycontroller.h"

InventoryController::InventoryController(ItemLoader *loader)
{
	m_itemLoader = loader;
}

QByteArray InventoryController::wearId(QByteArray id, QTcpSocket *player)
{
	if (m_inventories[player].contains(id))
		return m_wear[player].wearOn(id);
	return "";
}

QByteArray InventoryController::takeOff(QByteArray id, QTcpSocket *player)
{
	return m_wear[player].takeOff(id);
}
