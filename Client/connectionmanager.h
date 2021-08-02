#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QTcpSocket>
#include <QObject>
#include "enums.h"


class ConnectionManager : public QObject
{
	Q_OBJECT
public:
	explicit ConnectionManager();
	void connectToServer(QString ip, QString port);
	QByteArray getMap() { return m_map; }

	void movePlayer(playerMovement side);
	void actionPlayer(QString action, int side);
	void sendMessage(QString message) { m_socket->write("SAY:" + message.toUtf8()); }
	void changeName(QString name) { m_socket->write("NAME:" + name.toUtf8()); }

	void wearItem(QByteArray id) { m_socket->write("WEAR:" + id); }
	void takeOffItem(QByteArray id) { m_socket->write("TAKEOFF:" + id); }

private:
	void log(QString msg);

private slots:
	void connectedToServer();
	void socketReady();

signals:
	void dataReady();
	void connected();
	void gotMap();
	void playerPosition(QByteArray id, int x, int y);
	void message(QString message);
	void mapChanged(int x, int y, char object);
	void gotId(QByteArray id);
	void playerDisconnected(QByteArray id);
	void initPlayerPosition(position pos);
    void showHP(int HP);
	void pickItem(QByteArray id);
	void dropItem(QByteArray id);

	void placeItem(ItemInfo item);
	void removeItem(ItemInfo item);

	void signalWearItem(QByteArray id);
	void signalTakeOffItem(QByteArray id);

private:
	QTcpSocket *m_socket;
	QByteArray m_map;
};

#endif // CONNECTIONMANAGER_H
