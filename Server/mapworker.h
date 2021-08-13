#ifndef MAPWORKER_H
#define MAPWORKER_H

#include <QObject>
#include <QTcpSocket>
#include <QRandomGenerator>
#include <QTimer>
#include <QThread>

#include "utilities.h"
#include "healthcontrol.h"
#include "utilities.h"
#include "itemcontroller.h"
#include "inventorycontroller.h"
#include "../sharedItemLoader/itemloader.h"
#include "Electricity/electricitycontroller.h"

class MapWorker : public QObject
{
	Q_OBJECT
public:
	MapWorker(ItemLoader *loader, HealthControl *health);
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
    void processPlayerPush(QTcpSocket* buffer, actions act, QString direction);
    void processItemPush(position pos, QTcpSocket *socket, playerMovements side);
	void processPlayerKick(QTcpSocket* buffer, QString direction);
    void processPlayerPull(QTcpSocket* buffer, actions act, QString direction);
	void pushPlayer(playerMovements side,QTcpSocket* buffer);
	QByteArray getUserId(QTcpSocket* socket) { return m_playerIds[socket]; }
	void movePlayer(QTcpSocket *socket, playerMovements side);
	void processPlayerAction(QTcpSocket* socket, actions act, QString side);


	void processDrop(QTcpSocket *socket, QByteArray data, QByteArray bside);
	void processPick(QTcpSocket *socket, QString data);
	void pickItem(position pos, QTcpSocket *player);
	void dropItem(QByteArray id, position pos, QTcpSocket *player);

	void processDestroy(QTcpSocket *player, QByteArray side);
	void processBuild(QTcpSocket *player, QByteArray side, QByteArray id);

	bool checkBuildRequirementsMet(QTcpSocket *player, QByteArray id);
	void getResourcesFromPlayerForBuilding(QTcpSocket *player, QByteArray id);

	void destroyElementFromMap(position pos);
	void buildElementOnMap(position pos, QByteArray element);

	void startDynamite(QTcpSocket *client, QString direction);
signals:
	void sendToPlayer(QTcpSocket* player, QByteArray data);
	void sendToAll(QByteArray data);

private slots:
	void explode(position pos, int radius);

private:

	void explodeCell(position pos);

	void updateMapData(position pos, char object);

	void processPlayerMovement(position pos, QTcpSocket* socket);
	void formatMapChange(position pos, char object);
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
	HealthControl *m_healthController;
	ElectricityController *m_electricityController;
};

#endif // MAPWORKER_H
