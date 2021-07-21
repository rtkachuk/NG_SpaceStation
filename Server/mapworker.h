#ifndef MAPWORKER_H
#define MAPWORKER_H

#include <QObject>
#include <QTcpSocket>

struct position {
	int x;
	int y;
};

enum playerMovements {
	up,
	down,
	left,
	right
};

class MapWorker
{
public:
	MapWorker();
	void processMap(QByteArray mapData);
	bool checkMovementPosition(int x, int y);

	void addUser(QTcpSocket* socket);
	void removeUser(QTcpSocket* socket) { m_playerPositions.erase(m_playerPositions.find(socket)); }

	QByteArray getMovementResponse(QTcpSocket *socket, playerMovements side);
	void updatePlayerPos(QTcpSocket* socket, int x, int y);

private:
	QByteArray formatResponce (int x, int y) { return "POS" + QByteArray::number(x) + ":" + QByteArray::number(y);}
	QVector<QVector<char>> m_map;
	QMap<QTcpSocket*,position> m_playerPositions;
};

#endif // MAPWORKER_H
