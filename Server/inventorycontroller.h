#ifndef INVENTORYCONTROLLER_H
#define INVENTORYCONTROLLER_H

#include <QObject>
#include <QMap>
#include <QVector>
#include <QTcpSocket>
#include "playerwear.h"
#include "../sharedItemLoader/itemloader.h"
#include "../recipesLoader/recipesloader.h"

class InventoryController : public QObject
{
	Q_OBJECT
public:
	InventoryController(ItemLoader* loader);

	void createPlayerInventory(QTcpSocket *player) { QVector<QByteArray> inventory; m_inventories[player] = inventory; m_wear[player] = PlayerWear(m_itemLoader); }
	void destroyPlayerInventory(QTcpSocket *player) { m_inventories.remove(player); m_wear.remove(player); }
	bool addItemToInventory(QTcpSocket* player, QByteArray itemId);
	void removeItemFromInventory(QTcpSocket* player, QByteArray itemId) { m_inventories[player].removeOne(itemId); }
	int getItemsAmountInInventory(QTcpSocket* player, QByteArray itemId);

	bool checkPlayerExist(QTcpSocket* player) { return m_inventories.contains(player); }
	QVector<QByteArray> getPlayerInventory(QTcpSocket *player) { return m_inventories[player]; }

	void wearId(QByteArray id, QTcpSocket *player);
	void takeOff(QByteArray id, QTcpSocket *player);
	QByteArray getWear(playerWearable place, QTcpSocket *player) { return m_wear[player].getwear(place); }

	QVector<QByteArray> getRequirementsForCraftingRaw(QByteArray id) { return m_recipesLoader->getRequirementsRaw(id); }
	QMap<QByteArray, int> getRequirementsForCraftingTable(QByteArray id) { return m_recipesLoader->getRequirementsTable(id); }
	QList<QByteArray> getAvailableRecipes() { return m_recipesLoader->getAvaiableRecipes(); }
	QByteArray getToolRequiredForCrafting(QByteArray id) { return m_recipesLoader->getRequiredToolForCrafting(id); }

signals:
	void sendToPlayer(QTcpSocket* player, QByteArray data);
	void sendToAll(QByteArray data);

private:
	QMap<QTcpSocket*,QVector<QByteArray>> m_inventories;
	QMap<QTcpSocket*,PlayerWear> m_wear;
	ItemLoader* m_itemLoader;
	RecipesLoader* m_recipesLoader;

	int m_inventorySize = 45; // Rows * columns
};

#endif // INVENTORYCONTROLLER_H
