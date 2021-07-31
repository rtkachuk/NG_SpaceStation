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


bool MapWorker::checkMovementPosition(int x, int y)
{
	return m_map[y][x] == '.' ||
			m_map[y][x] == 'o' ||
			m_map[y][x] == '_';
}

QTcpSocket *MapWorker::checkPlayer(position pos)
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
    if(buffer==nullptr){
        return "";
    }
    position pushes = m_playerPositions[buffer];
    position playerToPushCords=getCoordsBySide(pushes.x,pushes.y,side);
    QTcpSocket *playerToPush=checkPlayer(playerToPushCords);
    if(playerToPush==nullptr) return "";
    switch (side) {
        case playerMovements::sup: return processPlayerMovement(playerToPushCords.x, playerToPushCords.y-1, playerToPush); break;
        case playerMovements::sdown: return processPlayerMovement(playerToPushCords.x, playerToPushCords.y+1, playerToPush); break;
        case playerMovements::sleft: return processPlayerMovement(playerToPushCords.x-1, playerToPushCords.y, playerToPush); break;
        case playerMovements::sright: return processPlayerMovement(playerToPushCords.x+1, playerToPushCords.y, playerToPush); break;
    }
	return "";
}

void MapWorker::addUser(QTcpSocket *socket, position pos)
{
	m_playerPositions[socket] = pos;
	m_playerIds[socket] = generateId();
}

QByteArray MapWorker::getMovementResponse(QTcpSocket *socket, playerMovements side)
{
	position pos = m_playerPositions[socket];

	switch (side) {
		case playerMovements::sup: return processPlayerMovement(pos.x, pos.y-1, socket); break;
		case playerMovements::sdown: return processPlayerMovement(pos.x, pos.y+1, socket); break;
		case playerMovements::sleft: return processPlayerMovement(pos.x-1, pos.y, socket); break;
		case playerMovements::sright: return processPlayerMovement(pos.x+1, pos.y, socket); break;
	}
	return "";
}

void MapWorker::updatePlayerPos(QTcpSocket* socket, int x, int y)
{
	position pos;
	pos.x = x;
	pos.y = y;
	m_playerPositions[socket] = pos;
}

QByteArray MapWorker::processPlayerAction(QTcpSocket *socket, actions act, QString direction)
{
	position pos = m_playerPositions[socket];
	playerMovements side = getSideFromString(direction);
    position actPos = getCoordsBySide(pos.x, pos.y, side);

	switch (act) {
		case actions::open: return formatMapChange(actPos.x, actPos.y, processOpen(actPos.x, actPos.y)); break;
		case actions::close: return formatMapChange(actPos.x, actPos.y, processClose(actPos.x, actPos.y)); break;
		default: return QByteArray("");
	}
}

QByteArray MapWorker::processPlayerMovement(int x, int y, QTcpSocket *socket)
{
	if (checkMovementPosition(x, y)) { updatePlayerPos(socket, x, y); return formatResponce(x, y, socket); }
    return "";
}

QByteArray MapWorker::generateId()
{
	QByteArray possibleChars("0123456789");
	int randomStringLength = 6;
	QByteArray id;

	for (int symbol = 0; symbol < randomStringLength; symbol++) {
		id += possibleChars.at(m_randomGenerator.bounded(0,possibleChars.length()));
	}
	return id;
}

void MapWorker::updateMapData(int x, int y, char object)
{
	int offset = 0;
	for (int row=0; row<y; row++) {
		offset += m_map[row].size() + 1;
	}
	offset += x;
	m_mapData[offset] = object;
	log ("Updated map");
}

QByteArray MapWorker::formatMapChange(int x, int y, char object)
{
	if (m_map[y][x] == object) {
		return "";
	}

	m_map[y][x] = object;
	updateMapData(x, y, object);
	return QByteArray("CHG:" + QByteArray::number(x) + ":" + QByteArray::number(y) + ":" + object + "|");
}

position MapWorker::getCoordsBySide(int x, int y, playerMovements side)
{
	position pos;
	pos.x = x;
	pos.y = y;
	switch (side) {
		case playerMovements::sup: pos.y--; break;
		case playerMovements::sdown: pos.y++; break;
		case playerMovements::sleft: pos.x--; break;
		case playerMovements::sright: pos.x++; break;
	}

	return pos;
}

playerMovements MapWorker::getSideFromString(QString side)
{
	if (side == "UP") return playerMovements::sup;
	if (side == "DOWN") return playerMovements::sdown;
	if (side == "LEFT") return playerMovements::sleft;
	if (side == "RIGHT") return playerMovements::sright;
	return playerMovements::sup;
}

QByteArray MapWorker::formatResponce(int x, int y, QTcpSocket *socket)
{
	return "POS:" + m_playerIds[socket] + ":" + QByteArray::number(x) + ":" + QByteArray::number(y) + "|";
}

char MapWorker::processOpen(int x, int y)
{
	switch(m_map[y][x]) {
		case 'c': return 'o';
		case 't': return 'T';
		case 's': return 'S';
		default: return m_map[y][x];
	}
}

char MapWorker::processClose(int x, int y)
{
	switch(m_map[y][x]) {
		case 'o': return 'c';
		case 'T': return 't';
		case 'S': return 's';
		default: return m_map[y][x];
	}
}

QVector<QByteArray> MapWorker::processDrop(QTcpSocket *socket, QByteArray data, QByteArray bside)
{
	position pos = m_playerPositions[socket];
	playerMovements side = getSideFromString(bside);
	position actPos = getCoordsBySide(pos.x, pos.y, side);
	return dropItem(data, actPos.x, actPos.y, socket);
}

QVector<QByteArray> MapWorker::processPick(QTcpSocket *socket, QString data)
{
	position pos = m_playerPositions[socket];
	playerMovements side = getSideFromString(data);
	position actPos = getCoordsBySide(pos.x, pos.y, side);

	return pickItem(actPos.x, actPos.y, socket);
}

QVector<QByteArray> MapWorker::pickItem(int x, int y, QTcpSocket *player)
{
	position coords;
	coords.x = x;
	coords.y = y;
	QByteArray id = m_itemController->getItem(coords);

	QVector<QByteArray> responce;

	if (id.isEmpty())
	{
		responce.push_back("");
		responce.push_back("");
	} else {
		m_inventoryController->addItemToInventory(player, id);
		m_itemController->deleteItem(coords, id);
		responce.push_back("PITEM:" + id + "|");
		responce.push_back("ICLEAR:" + QByteArray::number(x) + ":" + QByteArray::number(y) + ":" + id + "|");
	}

	return responce;
}

QVector<QByteArray> MapWorker::dropItem(QByteArray id, int x, int y, QTcpSocket *player)
{
	position coords;
	coords.x = x;
	coords.y = y;

	QVector<QByteArray> responce;
	log ("Item id to be dropped: " + id);

	if (id.isEmpty() || m_itemLoader->checkIdExist(id) == false) {
		responce.push_back("");
		responce.push_back("");
	} else {
		m_inventoryController->removeItemFromInventory(player, id);
		m_itemController->addItem(coords, id);
		responce.push_back("DITEM:" + id + "|");
		responce.push_back("IPLACE:" + QByteArray::number(x) + ":" + QByteArray::number(y) + ":" + id + "|");
		responce.push_back(m_inventoryController->takeOff(id, player));
	}

	return responce;
}

void MapWorker::log(QString msg)
{
	qDebug() << "[MapWorker]: " << msg;
}
