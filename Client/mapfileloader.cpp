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

	int lineNumber = 0;

	while (mapFile.atEnd() == false) {
		QByteArray line = mapFile.readLine();
		QVector<char> buffer;
		for (char cell : line) {
			if (cell != '\n')
				buffer.push_back(cell);
		}
		m_data.push_back(buffer);
		lineNumber++;
	}

	mapFile.close();
	log ("File loaded!");
}

void MapFileLoader::log(QString message)
{
	qDebug() << "[MapFileLoader]: " << message;
}

void MapFileLoader::clearMap()
{
	for (int row=0; row<m_data.size(); row++)
		m_data[row].clear();
	m_data.clear();
}
