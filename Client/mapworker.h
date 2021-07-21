#ifndef MAPWORKER_H
#define MAPWORKER_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QThread>

#include "mapfileloader.h"

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

	void setCellsColumns(int cellsColumns) { m_cellsColumns = cellsColumns; }
	void setCellsRows(int cellsRows) { m_cellsRows = cellsRows; }

	void setCellSizePixels(int size) { m_cellSizePixels = size; }
	int getCellSizePixels() { return m_cellSizePixels; }

	int getPlayerPosX() { return m_currentPlayerPositionX; }
	int getPlayerPosY() { return m_currentPlayerPositionY; }

	void mapInit();
	void dummyMapInit();

public slots:
	void drawMap();
	void updatePlayerPosition(playerMovements move);

private:
	bool checkPlayerCanMove(int x, int y);
	void log(QString message);

	MapFileLoader *m_fileLoader;


	int m_cellsColumns;
	int m_cellsRows;
	int m_cellSizePixels; // Cell size in pixels;

	QGraphicsScene *m_scene;
	QGraphicsPixmapItem *m_player;

	int m_currentPlayerPositionX = 1;
	int m_currentPlayerPositionY = 1;
	QVector <QVector<char>> m_map;
};

#endif // MAPWORKER_H
