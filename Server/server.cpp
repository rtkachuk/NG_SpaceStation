#include "server.h"

Server::Server()
{

}

void Server::log(QString msg)
{
	qDebug() << "[Server]: " << msg;
}

void Server::readyRead()
{
	QTcpSocket *client = (QTcpSocket*)sender();
	QByteArray data = client->readAll();

	log (data);
}

void Server::disconnected()
{
	QTcpSocket *client = (QTcpSocket*)sender();
	log ("Client " + client->peerAddress().toString() + " disconnected!");

	disconnect (client, &QTcpSocket::readyRead, this, &Server::readyRead);
	disconnect (client, &QTcpSocket::disconnected, this, &Server::disconnected);

	m_players.remove(m_players.indexOf(client));
}

void Server::incomingConnection(quintptr handle)
{
	QTcpSocket *client = new QTcpSocket();
	client->setSocketDescriptor(handle);
	m_players.append(client);

	log ("New connection from: " + client->peerAddress().toString() + "!");

	connect (client, &QTcpSocket::readyRead, this, &Server::readyRead);
	connect (client, &QTcpSocket::disconnected, this, &Server::disconnected);
}
