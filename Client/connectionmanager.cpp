#include "connectionmanager.h"

ConnectionManager::ConnectionManager()
{
	m_socket = new QTcpSocket();

	connect (m_socket, &QTcpSocket::connected, this, &ConnectionManager::connectedToServer);
	connect (m_socket, &QTcpSocket::readyRead, this, &ConnectionManager::socketReady);
	connect (m_socket, &QTcpSocket::disconnected, this, &ConnectionManager::connectionLost);
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

void ConnectionManager::processReceivedQuery(QByteArray data)
{
	log (data);
	QList<QByteArray> params = data.split(':');
	QByteArray command = params[0];

	if (command == "POS") {
		emit playerPosition(params[1], params[2].toInt(), params[3].toInt());
	}
	if (command == "CHG") {
		emit mapChanged(params[1].toInt(), params[2].toInt(), params[3].toStdString()[0]);
	}

	if (command == "IPLACE") {
		ItemInfo item;
		item.pos.x = params[1].toInt();
		item.pos.y = params[2].toInt();
		item.id = params[3];

		emit placeItem(item);
	}

	if (command == "ICLEAR") {
		ItemInfo item;
		item.pos.x = params[1].toInt();
		item.pos.y = params[2].toInt();
		item.id = params[3];

		emit removeItem(item);
	}

	if (command == "ID") {
		emit gotId(params[1]);
	}

	if (command == "DIS") {
		emit playerDisconnected(params[1]);
	}

	if (command == "SAY") {
		emit message(params[1] + ":" + params[2]);
	}

	if (command == "PITEM") {
		emit pickItem(params[1]);
	}

	if (command == "DITEM") {
		emit dropItem(params[1]);
	}

	if (command == "INIT") {
		position pos;

		pos.x = params[1].toInt();
		pos.y = params[2].toInt();

		emit initPlayerPosition(pos);
	}

	if (command == "MAP") {
		if (params[1] == "START") {
			emit mapLoadingStarted(params[2].toInt());
			m_map.clear();
		}
		if (params[1] == "BLOCK") {
			emit mapPartReceived(params[2].toInt());
			m_map += params[3];
		}
		if (params[1] == "END") {
			emit gotMap();
		}
	}

	if (command == "HEALTH"){
		int HP = params[1].toInt();
		emit showHP(HP);
	}

	if (command == "WEAR") {
		emit signalWearItem(params[1]);
	}

	if (command == "TAKEOFF") {
		emit signalTakeOffItem(params[1]);
	}

    if (command == "GEN") {
        emit generatorStatusUpdate(position(params[1].toInt(), params[2].toInt()), params[3]);
    }

    if (command == "NODE") {
        emit nodeStatusUpdate(position(params[1].toInt(), params[2].toInt()), params[3]);
    }
}

void ConnectionManager::connectedToServer()
{
	log ("Connected to " + m_socket->peerName());
	emit connected();
}

void ConnectionManager::socketReady()
{
	QByteArray received = m_socket->readAll();
	for (int i=0; i<received.size(); i++) {
		if (received[i] == '|') {
			processReceivedQuery(m_incomingDataBuffer);
			m_incomingDataBuffer.clear();
		}
		else
			m_incomingDataBuffer += received[i];
	}
}

void ConnectionManager::connectionLost()
{
	emit disconnected();
}
