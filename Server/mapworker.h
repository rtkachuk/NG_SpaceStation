#ifndef MAPWORKER_H
#define MAPWORKER_H

#include <QObject>
#include <QTcpSocket>
#include <QRandomGenerator>

#include "utilities.h"
#include "enums.h"
#include "itemcontroller.h"
#include "inventorycontroller.h"
#include "../sharedItemLoader/itemloader.h"

class MapWorker
{
public:
	MapWorker(ItemLoader *loader);
	void setInventoryController(InventoryController* inv) { m_inventoryController = inv; }
	void processMap(QByteArray mapData);
	void addUser(QTcpSocket* socket, position pos);
	void removeUser(QTcpSocket* socket) { m_playerPositions.erase(m_playerPositions.find(socket)); m_playerIds.erase(m_playerIds.find(socket)); }
	void updatePlayerPos(QTcpSocket* socket, int x, int y);

	bool checkMovementPosition(int x, int y);

	position getPlayerPosition(QTcpSocket *socket) { return m_playerPositions[socket]; }

	QTcpSocket* getPlayerByPosition(position pos);

	QMap<position, QVector<QByteArray>>* getAllItems() { return m_itemController->getItems(); }

	QByteArray getMap() { return m_mapData; }
    QByteArray processPlayerPush(QTcpSocket* buffer, actions act, QString direction);
    QByteArray getMovementPush(playerMovements side,QTcpSocket* buffer);
	QByteArray getUserId(QTcpSocket* socket) { return m_playerIds[socket]; }
	QByteArray getMovementResponse(QTcpSocket *socket, playerMovements side);
	QByteArray processPlayerAction(QTcpSocket* socket, actions act, QString side);


	QVector<QByteArray> processDrop(QTcpSocket *socket, QByteArray data, QByteArray bside);
	QVector<QByteArray> processPick(QTcpSocket *socket, QString data);
	QVector<QByteArray> pickItem(int x, int y, QTcpSocket *player);
	QVector<QByteArray> dropItem(QByteArray id, int x, int y, QTcpSocket *player);


private:
	QByteArray processPlayerMovement(position pos, QTcpSocket* socket);
	void updateMapData(int x, int y, char object);
	QByteArray formatMapChange(int x, int y, char object);

	playerMovements getSideFromString(QString side);
	QByteArray formatResponce (int x, int y, QTcpSocket* socket);

	char processOpen(int x, int y);
	char processClose(int x, int y);

	void log(QString msg);


	QRandomGenerator m_randomGenerator;

	QVector<QVector<char>> m_map;
	QByteArray m_mapData;
	QMap<QTcpSocket*,position> m_playerPositions;
	QMap<QTcpSocket*,QByteArray> m_playerIds;
    ItemController* m_itemController;
	InventoryController* m_inventoryController;
	ItemLoader* m_itemLoader;
};

#endif // MAPWORKER_H
