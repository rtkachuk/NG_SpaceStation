#include "server.h"

Server::Server()
{
	m_mapFileLoader = new MapFileLoader();
	m_mapWorker = new MapWorker();

	m_mapWorker->processMap(m_mapFileLoader->getMap());

	log ("Server ready");
}

void Server::log(QString msg)
{
	qDebug() << "[Server]: " << msg;
}

void Server::readyRead()
{
	QTcpSocket *client = (QTcpSocket*)sender();
	QByteArray data = client->readAll();

	if (data == "UP") { client->write(m_mapWorker->getMovementResponse(client, up)); }
	if (data == "DOWN") { client->write(m_mapWorker->getMovementResponse(client, down)); }
	if (data == "LEFT") { client->write(m_mapWorker->getMovementResponse(client, left)); }
	if (data == "RIGHT") { client->write(m_mapWorker->getMovementResponse(client, right)); }
}

void Server::disconnected()
{
	QTcpSocket *client = (QTcpSocket*)sender();
	log ("Client " + client->peerAddress().toString() + " disconnected!");

	disconnect (client, &QTcpSocket::readyRead, this, &Server::readyRead);
	disconnect (client, &QTcpSocket::disconnected, this, &Server::disconnected);

	m_players.remove(m_players.indexOf(client));
	m_mapWorker->removeUser(client);
}

void Server::incomingConnection(qintptr handle)
{
	QTcpSocket *client = new QTcpSocket();
	client->setSocketDescriptor(handle);

	m_players.append(client);
	m_mapWorker->addUser(client);

	log ("New connection from: " + client->peerAddress().toString() + "!");

	connect (client, &QTcpSocket::readyRead, this, &Server::readyRead);
	connect (client, &QTcpSocket::disconnected, this, &Server::disconnected);

	client->write("MAP_DATA" + m_mapFileLoader->getMap());
}
