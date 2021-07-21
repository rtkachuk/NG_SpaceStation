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
	return m_map[y][x] == '.';
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
		case up: if (checkMovementPosition(pos.x, pos.y-1)) { updatePlayerPos(socket, pos.x, pos.y-1); return formatResponce(pos.x, pos.y-1); } break;
		case down: if (checkMovementPosition(pos.x, pos.y+1)) { updatePlayerPos(socket, pos.x, pos.y+1); return formatResponce(pos.x, pos.y+1); } break;
		case left: if (checkMovementPosition(pos.x-1, pos.y)) { updatePlayerPos(socket, pos.x-1, pos.y); return formatResponce(pos.x-1, pos.y); } break;
		case right: if (checkMovementPosition(pos.x+1, pos.y)) { updatePlayerPos(socket, pos.x+1, pos.y); return formatResponce(pos.x+1, pos.y); } break;
	}
	return "NO";
}

void MapWorker::updatePlayerPos(QTcpSocket* socket, int x, int y)
{
	position pos;
	pos.x = x;
	pos.y = y;
	m_playerPositions[socket] = pos;
}
