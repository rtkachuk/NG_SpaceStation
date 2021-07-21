#ifndef MAPFILELOADER_H
#define MAPFILELOADER_H

#include <QFile>
#include <QDebug>

class MapFileLoader
{
public:
	MapFileLoader();
	void readMap();
	QVector<QVector<char>> getMap() { return m_data; }

	int getMapYSize() { return m_sizeY; }
	int getMapXSize() { return m_sizeX; }

private:
	void log(QString message);
	void clearMap();

	QVector<QVector<char>> m_data;
	int m_sizeY;
	int m_sizeX;
};

#endif // MAPFILELOADER_H
