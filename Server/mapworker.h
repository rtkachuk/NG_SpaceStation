#ifndef MAPWORKER_H
#define MAPWORKER_H

#include <QObject>
#include <QTcpSocket>
#include <QRandomGenerator>

struct position {
	int x;
	int y;
};

enum playerMovements {
	sup,
	sdown,
	sleft,
	sright
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
	void removeUser(QTcpSocket* socket) { m_playerPositions.erase(m_playerPositions.find(socket)); m_playerIds.erase(m_playerIds.find(socket)); }
	QByteArray getUserId(QTcpSocket* socket) { return m_playerIds[socket]; }

	QByteArray getMovementResponse(QTcpSocket *socket, playerMovements side);
	void updatePlayerPos(QTcpSocket* socket, int x, int y);
	QByteArray processPlayerAction(QTcpSocket* socket, actions act, QString side);

private:
	QByteArray generateId();
	void updateMapData(int x, int y, char object);
	QByteArray formatMapChange(int x, int y, char object);
	position getCoordsBySide (int x, int y, playerMovements side);
	playerMovements getSideFromString(QString side);
	QByteArray formatResponce (int x, int y, QTcpSocket* socket);

	char processOpen(int x, int y);
	char processClose(int x, int y);

	void log(QString msg);

	QRandomGenerator m_randomGenerator;

	QVector<QVector<char>> m_map;
	QByteArray m_mapData;
	QMap<QTcpSocket*,position> m_playerPositions;
	QMap<QTcpSocket*,QByteArray> m_playerIds;
};

#endif // MAPWORKER_H
