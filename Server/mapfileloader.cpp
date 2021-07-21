#include "mapfileloader.h"

MapFileLoader::MapFileLoader()
{
	readMap();
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

void MapFileLoader::log(QString message)
{
	qDebug() << "[MapFileLoader]: " << message;
}

void MapFileLoader::clearMap()
{
	m_map.clear();
}
