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

QByteArray ConnectionManager::loadData()
{
	return m_socket->readAll();
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
	log (data);
}
