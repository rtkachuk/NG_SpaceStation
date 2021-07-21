#ifndef MAPFILELOADER_H
#define MAPFILELOADER_H

#include <QVector>
#include <QDebug>
#include <QFile>

class MapFileLoader
{
public:
	MapFileLoader();
	void readMap();
	QByteArray getMap() { return m_map; }

private:
	void log(QString message);
	void clearMap();

	QByteArray m_map;
};

#endif // MAPFILELOADER_H
