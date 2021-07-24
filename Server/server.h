#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

#include "mapfileloader.h"
#include "mapworker.h"
#include "inventorycontroller.h"
#include "../sharedItemLoader/itemloader.h"

class Server : public QTcpServer
{
	Q_OBJECT
public:
	Server();

private:
	void sendToAll(QByteArray message);
	QString generateId();
	void chatMessageReceived(QTcpSocket *player, QByteArray message);

	void log(QString msg);

	QVector<QTcpSocket*> m_players;

	MapFileLoader *m_mapFileLoader;
	MapWorker *m_mapWorker;
	ItemLoader *m_itemLoader;
	InventoryController *m_inventoryController;

private slots:
	void readyRead();
	void disconnected();

protected:
	void incomingConnection(qintptr handle);
};

#endif // SERVER_H
