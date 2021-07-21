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
		case up: if (checkPlayerCanMove(m_currentPlayerPositionX, m_currentPlayerPositionY-1)) m_currentPlayerPositionY--; break;
		case down: if (checkPlayerCanMove(m_currentPlayerPositionX, m_currentPlayerPositionY+1)) m_currentPlayerPositionY++; break;
		case left: if (checkPlayerCanMove(m_currentPlayerPositionX-1, m_currentPlayerPositionY)) m_currentPlayerPositionX--; break;
		case right: if (checkPlayerCanMove(m_currentPlayerPositionX+1, m_currentPlayerPositionY)) m_currentPlayerPositionX++; break;
		default: log("Player moved worng!");
	}

	m_player->setPos(m_currentPlayerPositionX * 30, m_currentPlayerPositionY * 30);
}

bool MapWorker::checkPlayerCanMove(int x, int y)
{
	return m_map[y][x] == '.';
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
	m_player->setPos(m_currentPlayerPositionX * m_cellSizePixels, m_currentPlayerPositionY * m_cellSizePixels);
}

void MapWorker::log(QString message)
{
	qDebug() << "[MapWorker]: " << message;
}
