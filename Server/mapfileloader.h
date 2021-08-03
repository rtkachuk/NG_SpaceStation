#ifndef MAPFILELOADER_H
#define MAPFILELOADER_H

#include <QVector>
#include <QDebug>
#include <QFile>

#include "utilities.h"

class MapFileLoader
{
public:
	MapFileLoader();
	void readMap();
	void readPlayerPosition();
	QByteArray getMap() { return m_map; }
	position getPlayerPosition() { return m_playerPos; }

private:
	void log(QString message);
	void clearMap();

	QByteArray m_map;
	position m_playerPos;
};

#endif // MAPFILELOADER_H
