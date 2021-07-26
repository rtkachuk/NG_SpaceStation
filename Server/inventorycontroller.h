#ifndef INVENTORYCONTROLLER_H
#define INVENTORYCONTROLLER_H

#include <QMap>
#include <QVector>
#include <QTcpSocket>

class InventoryController
{
public:
	InventoryController();

	void createPlayerInventory(QTcpSocket *player) { QVector<QByteArray> inventory; m_inventories[player] = inventory; }
	void destroyPlayerInventory(QTcpSocket *player) { m_inventories.remove(player); }
	void addItemToInventory(QTcpSocket* player, QByteArray itemId) { m_inventories[player].push_back(itemId); }
	void removeItemFromInventory(QTcpSocket* player, QByteArray itemId) { m_inventories[player].removeOne(itemId); }

	bool checkPlayerExist(QTcpSocket* player) { return m_inventories.contains(player); }
	QVector<QByteArray> getPlayerInventory(QTcpSocket *player) { return m_inventories[player]; }

private:
	QMap<QTcpSocket*,QVector<QByteArray>> m_inventories;
};

#endif // INVENTORYCONTROLLER_H
