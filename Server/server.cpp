#include "server.h"

Server::Server()
{
	m_itemLoader = new ItemLoader();
	m_itemLoader->loadItems();

	m_mapFileLoader = new MapFileLoader();

	m_inventoryController = new InventoryController(m_itemLoader);
    m_healthController = new HealthControl();

	m_mapWorker = new MapWorker(m_itemLoader, m_healthController);

	m_mapWorker->setInventoryController(m_inventoryController);
	m_mapWorker->processMap(m_mapFileLoader->getMap());

	connect (m_mapWorker, &MapWorker::sendHealthInfo, this, &Server::notifyPlayerAboutDamage);

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
	QByteArray name = m_playerNames[player].toUtf8();
	sendToAll("SAY:" + name + ":" + message);
}

void Server::processNewPlayer(QTcpSocket* socket)
{
	position pos = m_mapFileLoader->getPlayerPosition();

	m_players.append(socket);
	m_mapWorker->addUser(socket, pos);
	m_inventoryController->createPlayerInventory(socket);
	m_healthController->setPlayerHealth(socket, 100);

	socket->write("INIT:" + QByteArray::number(pos.x) + ":" + QByteArray::number(pos.y) + "|");
	socket->write("MAP_DATA:" + m_mapWorker->getMap() + "|");
	socket->write("ID:" + m_mapWorker->getUserId(socket) + "|");
    socket->write(healthState(socket));
	sendAllItemsPositions(socket);
}

void Server::sendAllItemsPositions(QTcpSocket *socket)
{
	QMap<position, QVector<QByteArray>> *items = m_mapWorker->getAllItems();
	for (position pos : items->keys())
		for (QByteArray id : (*items)[pos])
			socket->write("IPLACE:" + QByteArray::number(pos.x) + ":" + QByteArray::number(pos.y) + ":" + id + "|");
}

void Server::log(QString msg)
{
	qDebug() << "[Server]: " << msg;
}

void Server::readyRead()
{
	QTcpSocket *client = (QTcpSocket*)sender();
	QByteArray recieved = client->readAll();
	QList<QByteArray> queries = recieved.split('|');
	for (QByteArray query : queries)
		processQuery(client, query);
}

void Server::disconnected()
{
	QTcpSocket *client = (QTcpSocket*)sender();
	log ("Client " + client->peerAddress().toString() + " disconnected!");

	disconnect (client, &QTcpSocket::readyRead, this, &Server::readyRead);
	disconnect (client, &QTcpSocket::disconnected, this, &Server::disconnected);

	QVector<QByteArray> inventory = m_inventoryController->getPlayerInventory(client);
	position playerPos = m_mapWorker->getPlayerPosition(client);
	for (QByteArray id : inventory) {
		QVector<QByteArray> responce = m_mapWorker->dropItem(id, playerPos, client);
		sendToAll(responce[1]);
	}

	m_players.remove(m_players.indexOf(client));
	sendToAll("DIS:" + m_mapWorker->getUserId(client));
	m_mapWorker->removeUser(client);
	m_inventoryController->destroyPlayerInventory(client);
	m_healthController->deleteHealth(client);
}

void Server::notifyPlayerAboutDamage(QTcpSocket *player)
{
	player->write(healthState(player));
}

void Server::processQuery(QTcpSocket *client, QByteArray query)
{
	QList<QByteArray> parts = query.split(':');
	QByteArray command = parts[0];
	if (command == "KICK") sendToAll(m_mapWorker->processPlayerKick(client,parts[1]));
	if (command == "PUSH") sendToAll(m_mapWorker->processPlayerPush(client,actions::push,parts[1]));
	if (command == "UP") { sendToAll(m_mapWorker->getMovementResponse(client, playerMovements::sup)); }
	if (command == "DOWN") { sendToAll(m_mapWorker->getMovementResponse(client, playerMovements::sdown)); }
	if (command == "LEFT") { sendToAll(m_mapWorker->getMovementResponse(client, playerMovements::sleft)); }
	if (command == "RIGHT") { sendToAll(m_mapWorker->getMovementResponse(client, playerMovements::sright)); }
	if (command == "OPEN") sendToAll(m_mapWorker->processPlayerAction(client, actions::open, parts[1]));
	if (command == "CLOSE") sendToAll(m_mapWorker->processPlayerAction(client, actions::close, parts[1]));
	if (command == "SAY") chatMessageReceived(client, parts[1]);
	if (command == "PICK") { QVector<QByteArray> result = m_mapWorker->processPick(client, parts[1]); client->write(result[0]); sendToAll(result[1]); }
	if (command == "DROP") { QVector<QByteArray> result = m_mapWorker->processDrop(client, parts[1], parts[2]); client->write(result[0]); client->write(result[2]); sendToAll(result[1]); }
	if (command == "NAME") { m_playerNames[client] = parts[1]; }
	if (command == "WEAR") { client->write(m_inventoryController->wearId(parts[1], client)); }
	if (command == "TAKEOFF") { client->write(m_inventoryController->takeOff(parts[1], client)); }
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
