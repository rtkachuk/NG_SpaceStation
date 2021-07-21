#ifndef MAPWORKER_H
#define MAPWORKER_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QThread>

// This class should load map from file like map.config
//

enum playerMovements {
	up,
	down,
	left,
	right
};

class MapWorker : public QObject
{
	Q_OBJECT
public:
	MapWorker();
	void setScene(QGraphicsScene *scene) { m_scene = scene; }

	void setCellSizePixels(int size) { m_cellSizePixels = size; }
	int getCellSizePixels() { return m_cellSizePixels; }

	int getPlayerPosX() { return m_currentPlayerPositionX; }
	int getPlayerPosY() { return m_currentPlayerPositionY; }

	void mapInit(QByteArray m_mapData);

	int getMapSizeX() { return m_mapSizeHorz * m_cellSizePixels; }
	int getMapSizeY() { return m_mapSizeVert * m_cellSizePixels; }

public slots:
	void drawMap();
	void updatePlayerPosition(int x, int y);

private:
	bool checkPlayerCanMove(int x, int y);
	void log(QString message);

	int m_cellSizePixels; // Cell size in pixels;
	int m_mapSizeVert;
	int m_mapSizeHorz;

	QGraphicsScene *m_scene;
	QGraphicsPixmapItem *m_player;

	int m_currentPlayerPositionX = 1;
	int m_currentPlayerPositionY = 1;
	QVector <QVector<char>> m_map;
	QByteArray m_mapData;
};

#endif // MAPWORKER_H
