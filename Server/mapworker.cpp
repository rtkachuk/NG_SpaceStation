#include "mapworker.h"

MapWorker::MapWorker(ItemLoader *loader)
{
	m_itemController = new ItemController();
	m_itemLoader = loader;
}

void MapWorker::processMap(QByteArray mapData)
{
	m_mapData = mapData;
	m_map.clear();

	QList<QByteArray> rows = mapData.split('\n');
	for (QByteArray line : rows) {
		int length = 0;
		QVector<char> buffer;
		for (char cell : line) {
			buffer.push_back(cell);
			length++;
		}
		m_map.push_back(buffer);
	}

    log ("Map loading done! (" + QByteArray::number(mapData.size()) + " bytes)");
}

QByteArray MapWorker::processPlayerPush(QTcpSocket *buffer, actions act, QString direction)
{
    playerMovements side = getSideFromString(direction);
	if (act == actions::push) return getMovementPush(side,buffer);
    return QByteArray("");
}


bool MapWorker::checkMovementPosition(position pos)
{
	return m_map[pos.y][pos.x] == '.' ||
			m_map[pos.y][pos.x] == 'o' ||
			m_map[pos.y][pos.x] == '_';
}

QTcpSocket *MapWorker::getPlayerByPosition(position pos)
{
    for(QTcpSocket* buffer : m_playerPositions.keys()){
        if(m_playerPositions[buffer].x==pos.x && m_playerPositions[buffer].y==pos.y){
            return buffer;
        }
    }
    return nullptr;
}

QByteArray MapWorker::getMovementPush(playerMovements side, QTcpSocket* buffer)
{
	if(buffer==nullptr) return "";

    position pushes = m_playerPositions[buffer];
	position playerToPushCords=Utilities::getCoordsBySide(pushes,side);
	QTcpSocket *playerToPush=getPlayerByPosition(playerToPushCords);

	if(playerToPush==nullptr) return "";

	return getMovementResponse(playerToPush, side);
}

void MapWorker::addUser(QTcpSocket *socket, position pos)
{
	m_playerPositions[socket] = pos;
	m_playerIds[socket] = Utilities::generateId();
}

QByteArray MapWorker::getMovementResponse(QTcpSocket *socket, playerMovements side)
{
	position pos = m_playerPositions[socket];

	switch (side) {
		case playerMovements::sup: pos.y--; break;
		case playerMovements::sdown: pos.y++; break;
		case playerMovements::sleft: pos.x--; break;
		case playerMovements::sright: pos.x++; break;
	}
	return processPlayerMovement(pos, socket);
}

void MapWorker::updatePlayerPos(QTcpSocket* socket, position pos)
{
	m_playerPositions[socket] = pos;
}

QByteArray MapWorker::processPlayerAction(QTcpSocket *socket, actions act, QString direction)
{
	position pos = m_playerPositions[socket];
	playerMovements side = getSideFromString(direction);
	position actPos = Utilities::getCoordsBySide(pos, side);

	switch (act) {
		case actions::open: return formatMapChange(actPos, processOpen(actPos)); break;
		case actions::close: return formatMapChange(actPos, processClose(actPos)); break;
		default: return QByteArray("");
	}
}

QByteArray MapWorker::processPlayerMovement(position pos, QTcpSocket *socket)
{
	if (checkMovementPosition(pos)) {
		updatePlayerPos(socket, pos);
		return formatResponce(pos, socket);
	}

    return "";
}

void MapWorker::updateMapData(position pos, char object)
{
	int offset = 0;
	for (int row=0; row<pos.y; row++) {
		offset += m_map[row].size() + 1;
	}
	offset += pos.x;
	m_mapData[offset] = object;
	log ("Updated map");
}

QByteArray MapWorker::formatMapChange(position pos, char object)
{
	if (m_map[pos.y][pos.x] == object) {
		return "";
	}

	m_map[pos.y][pos.x] = object;
	updateMapData(pos, object);
	return QByteArray("CHG:" + QByteArray::number(pos.x) + ":" + QByteArray::number(pos.y) + ":" + object + "|");
}

playerMovements MapWorker::getSideFromString(QString side)
{
	if (side == "UP") return playerMovements::sup;
	if (side == "DOWN") return playerMovements::sdown;
	if (side == "LEFT") return playerMovements::sleft;
	if (side == "RIGHT") return playerMovements::sright;
	return playerMovements::sup;
}

QByteArray MapWorker::formatResponce(position pos, QTcpSocket *socket)
{
	return "POS:" + m_playerIds[socket] + ":" + QByteArray::number(pos.x) + ":" + QByteArray::number(pos.y) + "|";
}

char MapWorker::processOpen(position pos)
{
	switch(m_map[pos.y][pos.x]) {
		case 'c': return 'o';
		case 't': return 'T';
		case 's': return 'S';
		default: return m_map[pos.y][pos.x];
	}
}

char MapWorker::processClose(position pos)
{
	switch(m_map[pos.y][pos.x]) {
		case 'o': return 'c';
		case 'T': return 't';
		case 'S': return 's';
		default: return m_map[pos.y][pos.x];
	}
}

QVector<QByteArray> MapWorker::processDrop(QTcpSocket *socket, QByteArray data, QByteArray bside)
{
	position pos = m_playerPositions[socket];
	playerMovements side = getSideFromString(bside);
	position actPos = Utilities::getCoordsBySide(pos, side);
	return dropItem(data, actPos, socket);
}

QVector<QByteArray> MapWorker::processPick(QTcpSocket *socket, QString data)
{
	position pos = m_playerPositions[socket];
	playerMovements side = getSideFromString(data);
	position actPos = Utilities::getCoordsBySide(pos, side);

	return pickItem(actPos, socket);
}

QVector<QByteArray> MapWorker::pickItem(position pos, QTcpSocket *player)
{
	QByteArray id = m_itemController->getItem(pos);

	QVector<QByteArray> responce;

	if (id.isEmpty())
	{
		responce.push_back("");
		responce.push_back("");
	} else {
		m_inventoryController->addItemToInventory(player, id);
		m_itemController->deleteItem(pos, id);
		responce.push_back("PITEM:" + id + "|");
		responce.push_back("ICLEAR:" + QByteArray::number(pos.x) + ":" + QByteArray::number(pos.y) + ":" + id + "|");
	}

	return responce;
}

QVector<QByteArray> MapWorker::dropItem(QByteArray id, position pos, QTcpSocket *player)
{
	QVector<QByteArray> responce;
	log ("Item id to be dropped: " + id);

	if (id.isEmpty() || m_itemLoader->checkIdExist(id) == false) {
		responce.push_back("");
		responce.push_back("");
	} else {
		m_inventoryController->removeItemFromInventory(player, id);
		m_itemController->addItem(pos, id);
		responce.push_back("DITEM:" + id + "|");
		responce.push_back("IPLACE:" + QByteArray::number(pos.x) + ":" + QByteArray::number(pos.y) + ":" + id + "|");
		responce.push_back(m_inventoryController->takeOff(id, player));
	}

	return responce;
}

void MapWorker::log(QString msg)
{
	qDebug() << "[MapWorker]: " << msg;
}
