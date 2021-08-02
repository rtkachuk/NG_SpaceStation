#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

#include "mapfileloader.h"
#include "mapworker.h"
#include "inventorycontroller.h"
#include <healthcontrol.h>

// Basic server flow:
// readyRead() -> processQuery() -> ...
//

class Server : public QTcpServer
{
	Q_OBJECT
public:
	Server();

private slots:
	void readyRead();
	void disconnected();

private:
	void processQuery(QTcpSocket *client, QByteArray query);

	void processNewPlayer(QTcpSocket *socket); // Create inventory, player position, etc.
	void sendAllItemsPositions(QTcpSocket* socket); // Send all items positions to new player

	void sendToAll(QByteArray message); // Send data to every user

	// Send chat message from one user to everybody from list
	//

	void chatMessageReceived(QTcpSocket *player, QByteArray message);

	void log(QString msg);

	QVector<QTcpSocket*> m_players;
	QMap<QTcpSocket*, QString> m_playerNames;

	MapFileLoader *m_mapFileLoader;
	MapWorker *m_mapWorker;
	InventoryController *m_inventoryController;
    HealthControl *m_healthController;
	ItemLoader* m_itemLoader;

protected:
	void incomingConnection(qintptr handle);
};

#endif // SERVER_H
