#include "mapworker.h"

MapWorker::MapWorker()
{

}

void MapWorker::processMap(QByteArray mapData)
{
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
}

bool MapWorker::checkMovementPosition(int x, int y)
{
	return m_map[y][x] == '.' || m_map[y][x] == 'o';
}

void MapWorker::addUser(QTcpSocket *socket)
{
	position pos;
	pos.x = 1;
	pos.y = 1;
	m_playerPositions[socket] = pos;
}

QByteArray MapWorker::getMovementResponse(QTcpSocket *socket, playerMovements side)
{
	position pos = m_playerPositions[socket];

	switch (side) {
		case playerMovements::up: if (checkMovementPosition(pos.x, pos.y-1)) { updatePlayerPos(socket, pos.x, pos.y-1); return formatResponce(pos.x, pos.y-1); } break;
		case playerMovements::down: if (checkMovementPosition(pos.x, pos.y+1)) { updatePlayerPos(socket, pos.x, pos.y+1); return formatResponce(pos.x, pos.y+1); } break;
		case playerMovements::left: if (checkMovementPosition(pos.x-1, pos.y)) { updatePlayerPos(socket, pos.x-1, pos.y); return formatResponce(pos.x-1, pos.y); } break;
		case playerMovements::right: if (checkMovementPosition(pos.x+1, pos.y)) { updatePlayerPos(socket, pos.x+1, pos.y); return formatResponce(pos.x+1, pos.y); } break;
	}
	return "Ай, вы ударились головой. Больно";
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
		case open: if (m_map[actPos.y][actPos.x] == 'c') { return formatMapChange(actPos.x, actPos.y, 'o'); } break;
		case close: if (m_map[actPos.y][actPos.x] == 'o') { return formatMapChange(actPos.x, actPos.y, 'c'); } break;
	}
	return QByteArray("Я не особо понимаю: что мне нужно делать?");
}

QByteArray MapWorker::formatMapChange(int x, int y, char object)
{
	m_map[y][x] = object;
	return QByteArray("CHG" + QByteArray::number(x) + ":" + QByteArray::number(y) + ":" + object);
}

position MapWorker::getCoordsBySide(int x, int y, playerMovements side)
{
	position pos;
	pos.x = x;
	pos.y = y;
	switch (side) {
		case up: pos.y--; break;
		case down: pos.y++; break;
		case left: pos.x--; break;
		case right: pos.x++; break;
	}

	return pos;
}

playerMovements MapWorker::getSideFromString(QString side)
{
	if (side == "UP") return up;
	if (side == "DOWN") return down;
	if (side == "LEFT") return left;
	if (side == "RIGHT") return right;
}
