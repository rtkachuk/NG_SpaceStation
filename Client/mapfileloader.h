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

private:
	void log(QString message);
	void clearMap();

	QVector<QVector<char>> m_data;
};

#endif // MAPFILELOADER_H
