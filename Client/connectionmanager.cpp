#include "connectionmanager.h"

ConnectionManager::ConnectionManager()
{
	m_socket = new QTcpSocket();

	connect (m_socket, &QTcpSocket::connected, this, &ConnectionManager::connectedToServer);
	connect (m_socket, &QTcpSocket::readyRead, this, &ConnectionManager::socketReady);
}

void ConnectionManager::connectToServer(QString ip, QString port)
{
	m_socket->connectToHost(ip, port.toUInt());
}

void ConnectionManager::movePlayer(playerMovement side)
{
	switch(side) {
		case moveUp: m_socket->write("UP"); break;
		case moveDown: m_socket->write("DOWN"); break;
		case moveLeft: m_socket->write("LEFT"); break;
		case moveRight: m_socket->write("RIGHT"); break;
	}
}

void ConnectionManager::actionPlayer(QString action, int side)
{
	QByteArray direction = "UP";

	switch (side) {
		case 2: direction = "DOWN"; break;
		case 3: direction = "LEFT"; break;
		case 4: direction = "RIGHT"; break;
	}
	log (action.toUtf8() + ":" + direction);
	m_socket->write(QByteArray(action.toUtf8()) + ":" + direction);
}

void ConnectionManager::log(QString msg)
{
	qDebug() << "[ConnectionManager]: " << msg;
}

void ConnectionManager::connectedToServer()
{
	log ("Connected to " + m_socket->peerName());
	emit connected();
}

void ConnectionManager::socketReady()
{
	QByteArray received = m_socket->readAll();

	QList<QByteArray> gotData = received.split('|');

	for (QByteArray data : gotData) {

		log (data);

		if (data.indexOf("POS") != -1) {
			data.remove(0, QByteArray("POS").size());
			QList<QByteArray> position = data.split(':');
			emit playerPosition(position[0], position[1].toInt(), position[2].toInt());
			return;
		}
		if (data.indexOf("CHG") != -1) {
			log ("Map changed!");
			data.remove(0, QByteArray("CHG").size());
			QList<QByteArray> changed = data.split(':');
			emit mapChanged(changed[0].toInt(), changed[1].toInt(), changed[2].toStdString()[0]);
			return;
		}

		if (data.indexOf("ID") != -1) {
			log ("Received ID");
			data.remove(0, QByteArray("ID").size());
			emit gotId(data);
			return;
		}

		if (data.indexOf("DIS") != -1) {
			log ("Some player disconnected...");
			data.remove(0, QByteArray("DIS").size());
			emit playerDisconnected(data);
			return;
		}

		if (data.indexOf("SAY") != -1) {
			QList<QByteArray> messageInfo = data.split(':');
			emit message(messageInfo[1] + ":" + messageInfo[2]);
			return;
		}

		if (data.indexOf("PITEM") != -1) {
			emit pickItem(data.split(':')[1]);
			return;
		}

		if (data.indexOf("DITEM") != -1) {
			emit dropItem(data.split(':')[1]);
			return;
		}

		if (data.indexOf("INIT") != -1) {
			log ("Got init player position");
			position pos;
			QList<QByteArray> dataInit = data.split(':');

			pos.x = dataInit[1].toInt();
			pos.y = dataInit[2].toInt();

			emit initPlayerPosition(pos);

			log ("Received map!");
			m_map = dataInit[4];
			emit gotMap();

			return;
		}

		emit message(data);
	}
}
