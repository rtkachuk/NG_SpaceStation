#include "mapworker.h"

MapWorker::MapWorker()
{
	m_fileLoader = new MapFileLoader();
}

void MapWorker::mapInit()
{
	m_map = m_fileLoader->getMap();
}

void MapWorker::updatePlayerPosition(playerMovements move)
{
	switch (move) {
		case up: if (checkPlayerCanMove(m_initialPlayerPositionX, m_initialPlayerPositionY-1)) m_initialPlayerPositionY--; break;
		case down: if (checkPlayerCanMove(m_initialPlayerPositionX, m_initialPlayerPositionY+1)) m_initialPlayerPositionY++; break;
		case left: if (checkPlayerCanMove(m_initialPlayerPositionX-1, m_initialPlayerPositionY)) m_initialPlayerPositionX--; break;
		case right: if (checkPlayerCanMove(m_initialPlayerPositionX+1, m_initialPlayerPositionY)) m_initialPlayerPositionX++; break;
		default: log("Player moved worng!");
	}

	m_player->setPos(m_initialPlayerPositionX * 30, m_initialPlayerPositionY * 30);
}

bool MapWorker::checkPlayerCanMove(int x, int y)
{
	return m_map[y][x] == '.';
}

void MapWorker::dummyMapInit()
{
	m_map.resize(m_cellsRows);
	for (int i=0; i< m_cellsRows; i++) {
		m_map[i].resize(m_cellsColumns);
	}

	for (int row = 0; row < m_map.size(); row++) {
		for (int cell = 0; cell < m_map.at(row).size(); cell++)
			m_map[row][cell] = '.';
	}
}

void MapWorker::drawMap()
{
	int currentY = 0;
	int currentX = 0;
	for (QVector<char> row : m_map) {
		for (char cell : row) {
			switch (cell) {
				case '.': m_scene->addPixmap(QPixmap(":/buildings/floor.png"))->setPos(currentX, currentY); break;
				case '#': m_scene->addPixmap(QPixmap(":/buildings/wall.png"))->setPos(currentX, currentY); break;
				default: m_scene->addRect(currentX, currentY, m_cellSizePixels, m_cellSizePixels);
			}
			currentX += m_cellSizePixels;
		}
		currentX = 0;
		currentY += m_cellSizePixels;
	}
	m_player = m_scene->addPixmap(QPixmap(":/players/player.png"));
	m_player->setPos(m_initialPlayerPositionX * m_cellSizePixels, m_initialPlayerPositionY * m_cellSizePixels);
}

void MapWorker::log(QString message)
{
	qDebug() << "[MapWorker]: " << message;
}
