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

enum actions {
	open,
	close
};

class MapWorker
{
public:
	MapWorker();
	void processMap(QByteArray mapData);
	QByteArray getMap() { return m_mapData; }

	bool checkMovementPosition(int x, int y);

	void addUser(QTcpSocket* socket);
	void removeUser(QTcpSocket* socket) { m_playerPositions.erase(m_playerPositions.find(socket)); }

	QByteArray getMovementResponse(QTcpSocket *socket, playerMovements side);
	void updatePlayerPos(QTcpSocket* socket, int x, int y);
	QByteArray processPlayerAction(QTcpSocket* socket, actions act, QString side);

private:
	void updateMapData(int x, int y, char object);
	QByteArray formatMapChange(int x, int y, char object);
	position getCoordsBySide (int x, int y, playerMovements side);
	playerMovements getSideFromString(QString side);
	QByteArray formatResponce (int x, int y) { return "POS" + QByteArray::number(x) + ":" + QByteArray::number(y);}

	void log(QString msg);

	QVector<QVector<char>> m_map;
	QByteArray m_mapData;
	QMap<QTcpSocket*,position> m_playerPositions;
};

#endif // MAPWORKER_H
