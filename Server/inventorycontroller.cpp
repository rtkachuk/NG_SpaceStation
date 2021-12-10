#include "inventorycontroller.h"

InventoryController::InventoryController(ItemLoader *loader)
{
	m_itemLoader = loader;
	m_recipesLoader = new RecipesLoader();
}

bool InventoryController::addItemToInventory(QTcpSocket *player, QByteArray itemId) {
	if (m_inventories[player].size() < m_inventorySize) {
		m_inventories[player].push_back(itemId);
		return true;
	}
	else {
		return false;
	}
}

int InventoryController::getItemsAmountInInventory(QTcpSocket *player, QByteArray itemId)
{
	int amount = 0;
	QVector<QByteArray> inventory = m_inventories[player];
	for (QByteArray id : inventory) {
		if (id == itemId)
			amount++;
	}
	return amount;
}

void InventoryController::wearId(QByteArray id, QTcpSocket *player)
{
	if (m_inventories[player].contains(id))
		emit sendToPlayer(player, m_wear[player].wearOn(id));
}

void InventoryController::takeOff(QByteArray id, QTcpSocket *player)
{
	emit sendToPlayer(player, m_wear[player].takeOff(id));
}
