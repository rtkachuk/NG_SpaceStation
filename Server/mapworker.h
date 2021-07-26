#ifndef MAPWORKER_H
#define MAPWORKER_H

#include <QObject>
#include <QTcpSocket>
#include <QRandomGenerator>

#include "enums.h"
#include "itemcontroller.h"
#include "inventorycontroller.h"
#include "../sharedItemLoader/itemloader.h"

class MapWorker
{
public:
	MapWorker();
	void processMap(QByteArray mapData);
	QByteArray getMap() { return m_mapData; }
    QByteArray processPlayerPush(QTcpSocket* buffer, actions act, QString direction);
	bool checkMovementPosition(int x, int y);
    QTcpSocket* checkPlayer(position pos);
    QByteArray getMovementPush(playerMovements side,QTcpSocket* buffer);
    QString getSide(QString data);
	void addUser(QTcpSocket* socket, position pos);
	void removeUser(QTcpSocket* socket) { m_playerPositions.erase(m_playerPositions.find(socket)); m_playerIds.erase(m_playerIds.find(socket)); }
	QByteArray getUserId(QTcpSocket* socket) { return m_playerIds[socket]; }
	QByteArray getMovementResponse(QTcpSocket *socket, playerMovements side);
	void updatePlayerPos(QTcpSocket* socket, int x, int y);
	QByteArray processPlayerAction(QTcpSocket* socket, actions act, QString side);

	void setInventoryController(InventoryController* inv) { m_inventoryController = inv; }
	QVector<QByteArray> processDrop(QTcpSocket *socket, QByteArray data);
	QVector<QByteArray> processPick(QTcpSocket *socket, QString data);
	position getPlayerPosition(QTcpSocket *socket) { return m_playerPositions[socket]; }
	QMap<position, QVector<QByteArray>>* getAllItems() { return m_itemController->getItems(); }
private:
	QByteArray processPlayerMovement(int x, int y, QTcpSocket* socket);
	QByteArray generateId();
	void updateMapData(int x, int y, char object);
	QByteArray formatMapChange(int x, int y, char object);
	position getCoordsBySide (int x, int y, playerMovements side);
	playerMovements getSideFromString(QString side);
	QByteArray formatResponce (int x, int y, QTcpSocket* socket);

	char processOpen(int x, int y);
	char processClose(int x, int y);

	QVector<QByteArray> pickItem(int x, int y, QTcpSocket *player);
	QVector<QByteArray> dropItem(QByteArray id, int x, int y, QTcpSocket *player);

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
