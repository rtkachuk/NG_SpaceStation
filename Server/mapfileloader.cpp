#include "mapfileloader.h"

MapFileLoader::MapFileLoader()
{
	readMap();
	readPlayerPosition();
}

void MapFileLoader::readMap()
{
	log ("Cleanin up");
	clearMap();
	log ("Loading file map.txt");

	QFile mapFile("map.txt");

	if (mapFile.open(QIODevice::ReadOnly) == false) {
		log ("Error opening file: " + mapFile.errorString());
		return;
	}

	m_map = mapFile.readAll();
	mapFile.close();
	log ("File loaded!");
}

void MapFileLoader::readPlayerPosition()
{
	log ("Loading player positions");
	QFile positionFile("playerPos.txt");

	if (positionFile.open(QIODevice::ReadOnly) == false) {
		log ("Error opening file: " + positionFile.errorString());
		return;
	}
	QList<QByteArray> data = positionFile.readLine().split(':');
	m_playerPos.x = data[0].toInt();
	m_playerPos.y = data[1].toInt();
}

void MapFileLoader::log(QString message)
{
	qDebug() << "[MapFileLoader]: " << message;
}

void MapFileLoader::clearMap()
{
	m_map.clear();
}
