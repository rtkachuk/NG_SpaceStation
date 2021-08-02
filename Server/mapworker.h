#ifndef MAPWORKER_H
#define MAPWORKER_H

#include <QObject>
#include <QTcpSocket>
#include <QRandomGenerator>

#include "utilities.h"
#include "healthcontrol.h"
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
	void updatePlayerPos(QTcpSocket* socket, position pos);

	bool checkMovementPosition(position pos);

	position getPlayerPosition(QTcpSocket *socket) { return m_playerPositions[socket]; }

	QTcpSocket* getPlayerByPosition(position pos);

	QMap<position, QVector<QByteArray>>* getAllItems() { return m_itemController->getItems(); }

	QByteArray getMap() { return m_mapData; }
    QByteArray processPlayerPush(QTcpSocket* buffer, actions act, QString direction);
    QByteArray processPlayerKick(QTcpSocket* buffer, actions act, QString direction);
    QByteArray getMovementPush(playerMovements side,QTcpSocket* buffer);
    QByteArray getMovementKick(playerMovements side,QTcpSocket* buffer);
	QByteArray getUserId(QTcpSocket* socket) { return m_playerIds[socket]; }
	QByteArray getMovementResponse(QTcpSocket *socket, playerMovements side);
	QByteArray processPlayerAction(QTcpSocket* socket, actions act, QString side);


	QVector<QByteArray> processDrop(QTcpSocket *socket, QByteArray data, QByteArray bside);
	QVector<QByteArray> processPick(QTcpSocket *socket, QString data);
	QVector<QByteArray> pickItem(position pos, QTcpSocket *player);
	QVector<QByteArray> dropItem(QByteArray id, position pos, QTcpSocket *player);


private:
	void updateMapData(position pos, char object);

	QByteArray processPlayerMovement(position pos, QTcpSocket* socket);
	QByteArray formatMapChange(position pos, char object);
	QByteArray formatResponce (position pos, QTcpSocket* socket);

	playerMovements getSideFromString(QString side);

	char processOpen(position pos);
	char processClose(position pos);

	void log(QString msg);


	QRandomGenerator m_randomGenerator;

	QVector<QVector<char>> m_map;
	QByteArray m_mapData;
	QMap<QTcpSocket*,position> m_playerPositions;
	QMap<QTcpSocket*,QByteArray> m_playerIds;
    ItemController* m_itemController;
	InventoryController* m_inventoryController;
	ItemLoader* m_itemLoader;
    HealthControl *m_healthControll;
};

#endif // MAPWORKER_H
