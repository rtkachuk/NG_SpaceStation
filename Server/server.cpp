#include "server.h"

Server::Server()
{
	m_mapFileLoader = new MapFileLoader();
	m_mapWorker = new MapWorker();
	m_inventoryController = new InventoryController();

	m_mapWorker->setInventoryController(m_inventoryController);

	m_mapWorker->processMap(m_mapFileLoader->getMap());

	log ("Server ready");
}

void Server::sendToAll(QByteArray message)
{
	for (QTcpSocket* client : m_players) {
		client->write(message);
	}
}

void Server::chatMessageReceived(QTcpSocket *player, QByteArray(message))
{
	QByteArray id = m_mapWorker->getUserId(player);
	sendToAll("SAY:" + id + ":" + message.split(':')[1]);
}

void Server::processNewPlayer(QTcpSocket* socket)
{
	position pos = m_mapFileLoader->getPlayerPosition();

	m_players.append(socket);
	m_mapWorker->addUser(socket, pos);
	m_inventoryController->createPlayerInventory(socket);

	socket->write("INIT:" + QByteArray::number(pos.x) + ":" + QByteArray::number(pos.y) + ":MAP_DATA:" + m_mapWorker->getMap());
}

void Server::log(QString msg)
{
	qDebug() << "[Server]: " << msg;
}

void Server::readyRead()
{
	QTcpSocket *client = (QTcpSocket*)sender();
	QByteArray data = client->readAll();

	if (data == "UP") { sendToAll(m_mapWorker->getMovementResponse(client, playerMovements::sup)); }
	if (data == "DOWN") { sendToAll(m_mapWorker->getMovementResponse(client, playerMovements::sdown)); }
	if (data == "LEFT") { sendToAll(m_mapWorker->getMovementResponse(client, playerMovements::sleft)); }
	if (data == "RIGHT") { sendToAll(m_mapWorker->getMovementResponse(client, playerMovements::sright)); }
	if (data.indexOf("OPEN") != -1) sendToAll(m_mapWorker->processPlayerAction(client, actions::open, data.split(':')[1]));
	if (data.indexOf("CLOSE") != -1) sendToAll(m_mapWorker->processPlayerAction(client, actions::close, data.split(':')[1]));
	if (data == "ASKID") { client->write("ID" + m_mapWorker->getUserId(client)); }
	if (data.indexOf("SAY") != -1) chatMessageReceived(client, data);
	if (data.indexOf("PICK") != -1) client->write(m_mapWorker->processPlayerAction(client, actions::pick, data.split(':')[1]));
	if (data.indexOf("DROP") != -1) client->write(m_mapWorker->processDrop(client, data));
}

void Server::disconnected()
{
	QTcpSocket *client = (QTcpSocket*)sender();
	log ("Client " + client->peerAddress().toString() + " disconnected!");

	disconnect (client, &QTcpSocket::readyRead, this, &Server::readyRead);
	disconnect (client, &QTcpSocket::disconnected, this, &Server::disconnected);

	m_players.remove(m_players.indexOf(client));
	sendToAll("DIS" + m_mapWorker->getUserId(client));
	m_mapWorker->removeUser(client);
	m_inventoryController->destroyPlayerInventory(client);
}

void Server::incomingConnection(qintptr handle)
{
	QTcpSocket *client = new QTcpSocket();
	client->setSocketDescriptor(handle);

	log ("New connection from: " + client->peerAddress().toString() + "!");

	connect (client, &QTcpSocket::readyRead, this, &Server::readyRead);
	connect (client, &QTcpSocket::disconnected, this, &Server::disconnected);

	processNewPlayer(client);
}
