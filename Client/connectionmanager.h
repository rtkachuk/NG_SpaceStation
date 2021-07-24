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
	void askForId() { m_socket->write("ASKID");};

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

private:
	QTcpSocket *m_socket;
	QByteArray m_map;

};

#endif // CONNECTIONMANAGER_H
