#ifndef MAPWORKER_H
#define MAPWORKER_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QThread>
#include <QRandomGenerator>
#include "enums.h"
#include "../sharedItemLoader/itemloader.h"

// This class should load map from file like map.config
//

class MapWorker : public QObject
{
	Q_OBJECT
public:
	MapWorker();

	void setPlayerId(QByteArray id) { m_playerId = id; }
	void setScene(QGraphicsScene *scene) { m_scene = scene; }

	void setCellSizePixels(int size) { m_cellSizePixels = size; }
	int getCellSizePixels() { return m_cellSizePixels; }

	QByteArray getPlayerId() { return m_playerId; }

	int getPlayerPosX() { return m_currentPlayerPositionX; }
	int getPlayerPosY() { return m_currentPlayerPositionY; }

	void mapInit(QByteArray m_mapData);

	int getMapSizeX() { return m_mapSizeHorz * m_cellSizePixels; }
	int getMapSizeY() { return m_mapSizeVert * m_cellSizePixels; }

	void removePlayer(QByteArray id);

	void setBasicPlayerPosition(position pos) { m_currentPlayerPositionX = pos.x; m_currentPlayerPositionY = pos.y; }

	void setItemLoader(ItemLoader* loader) { m_itemLoader = loader; }

public slots:
	void drawMap();
	void updatePlayerPosition(QByteArray id, int x, int y);
	void updateMap(int x, int y, char object);
	void placeItem(ItemInfo item);
	void removeItem(ItemInfo item);

private:
	void constructCell(int x, int y, QString image);
	void updateCell(int x, int y, char object);
	QPixmap selectSpacePixmap();
	void log(QString message);

	int m_cellSizePixels; // Cell size in pixels;
	int m_mapSizeVert = 1000;
	int m_mapSizeHorz = 1000;

	QGraphicsScene *m_scene;
	QGraphicsPixmapItem *m_player;
	QByteArray m_playerId;
	QMap<QByteArray, QGraphicsPixmapItem*> m_players;

	int m_currentPlayerPositionX = 0;
	int m_currentPlayerPositionY = 0;
	QVector <QVector<char>> m_map;
	QByteArray m_mapData;
	bool side = false;

	QVector<QString> m_spacePixmaps;
	QRandomGenerator m_randomGenerator;
	ItemLoader* m_itemLoader;

	QMap<ItemInfo, QVector<QGraphicsPixmapItem*>> m_items;
};

#endif // MAPWORKER_H
