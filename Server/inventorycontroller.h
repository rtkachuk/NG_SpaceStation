#ifndef INVENTORYCONTROLLER_H
#define INVENTORYCONTROLLER_H

#include <QMap>
#include <QVector>
#include <QTcpSocket>
#include "playerwear.h"
#include "../sharedItemLoader/itemloader.h"

class InventoryController
{
public:
	InventoryController(ItemLoader* loader);

	void createPlayerInventory(QTcpSocket *player) { QVector<QByteArray> inventory; m_inventories[player] = inventory; m_wear[player] = PlayerWear(m_itemLoader); }
	void destroyPlayerInventory(QTcpSocket *player) { m_inventories.remove(player); m_wear.remove(player); }
	void addItemToInventory(QTcpSocket* player, QByteArray itemId) { m_inventories[player].push_back(itemId); }
	void removeItemFromInventory(QTcpSocket* player, QByteArray itemId) { m_inventories[player].removeOne(itemId); }

	bool checkPlayerExist(QTcpSocket* player) { return m_inventories.contains(player); }
	QVector<QByteArray> getPlayerInventory(QTcpSocket *player) { return m_inventories[player]; }

	QByteArray wearId(QByteArray id, QTcpSocket *player);
	QByteArray takeOff(QByteArray id, QTcpSocket *player);
	QByteArray getWear(playerWearable place, QTcpSocket *player) { return m_wear[player].getwear(place); }

private:
	QMap<QTcpSocket*,QVector<QByteArray>> m_inventories;
	QMap<QTcpSocket*,PlayerWear> m_wear;
	ItemLoader* m_itemLoader;
};

#endif // INVENTORYCONTROLLER_H
