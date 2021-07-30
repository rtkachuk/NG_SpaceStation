#include "server.h"

Server::Server()
{
	m_itemLoader = new ItemLoader();
	m_itemLoader->loadItems();

	m_mapFileLoader = new MapFileLoader();
	m_mapWorker = new MapWorker(m_itemLoader);

	m_inventoryController = new InventoryController(m_itemLoader);
    m_healthController = new HealthControl();

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
	QByteArray name = m_playerNames[player].toUtf8();
	sendToAll("SAY:" + name + ":" + message.split(':')[1]);
}

void Server::processNewPlayer(QTcpSocket* socket)
{
	position pos = m_mapFileLoader->getPlayerPosition();

	m_players.append(socket);
	m_mapWorker->addUser(socket, pos);
	m_inventoryController->createPlayerInventory(socket);
    m_healthController->createPlayerHealth(socket);

	socket->write("INIT:" + QByteArray::number(pos.x) + ":" + QByteArray::number(pos.y) + "|");
	socket->write("MAP_DATA:" + m_mapWorker->getMap() + "|");
	socket->write("ID:" + m_mapWorker->getUserId(socket) + "|");
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
    QByteArray data = client->readAll();
    if (data.indexOf("PUSH")!=-1) sendToAll(m_mapWorker->processPlayerPush(client,actions::push,data.split(':')[1]));
	if (data == "UP") { sendToAll(m_mapWorker->getMovementResponse(client, playerMovements::sup)); }
	if (data == "DOWN") { sendToAll(m_mapWorker->getMovementResponse(client, playerMovements::sdown)); }
	if (data == "LEFT") { sendToAll(m_mapWorker->getMovementResponse(client, playerMovements::sleft)); }
	if (data == "RIGHT") { sendToAll(m_mapWorker->getMovementResponse(client, playerMovements::sright)); }
	if (data.indexOf("OPEN") != -1) sendToAll(m_mapWorker->processPlayerAction(client, actions::open, data.split(':')[1]));
	if (data.indexOf("CLOSE") != -1) sendToAll(m_mapWorker->processPlayerAction(client, actions::close, data.split(':')[1]));
	if (data.indexOf("SAY") != -1) chatMessageReceived(client, data);
	if (data.indexOf("PICK") != -1) { QVector<QByteArray> result = m_mapWorker->processPick(client, data); client->write(result[0]); sendToAll(result[1]); }
	if (data.indexOf("DROP") != -1) { QVector<QByteArray> result = m_mapWorker->processDrop(client, data); client->write(result[0]); client->write(result[2]); sendToAll(result[1]); }
	if (data.indexOf("NAME") != -1) { m_playerNames[client] = data.split(':')[1]; }
	if (data.indexOf("WEAR") != -1) { client->write(m_inventoryController->wearId(data.split(':')[1], client)); }
	if (data.indexOf("TAKEOFF") != -1) { client->write(m_inventoryController->takeOff(data.split(':')[1], client)); }
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
		QVector<QByteArray> responce = m_mapWorker->dropItem(id, playerPos.x, playerPos.y, client);
		sendToAll(responce[1]);
	}

	m_players.remove(m_players.indexOf(client));
	sendToAll("DIS:" + m_mapWorker->getUserId(client));
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
