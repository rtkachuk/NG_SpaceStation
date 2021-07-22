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
	QByteArray data = m_socket->readAll();
	log ("Received: " + QString::number(data.size()) + " bytes");
	if (data.indexOf("MAP_DATA") != -1) {
		log ("Received map!");
		data.remove(0, QByteArray("MAP_DATA").size());
		m_map = data;
		emit gotMap();
		return;
	}
	if (data.indexOf("POS") != -1) {
		log ("Received POS");
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
	emit message(data);
}
