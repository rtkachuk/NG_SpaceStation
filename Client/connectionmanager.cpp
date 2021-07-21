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
	}
	if (data.indexOf("POS") != -1) {
		log ("Received POS");
		data.remove(0, QByteArray("POS").size());
		QList<QByteArray> position = data.split(':');
		emit playerPosition(position[0].toInt(), position[1].toInt());

	}
}
