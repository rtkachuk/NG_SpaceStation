#include "mapworker.h"

MapWorker::MapWorker()
{
}

void MapWorker::mapInit(QByteArray mapData)
{
	m_map.clear();

	m_mapSizeHorz = 0;
	m_mapSizeVert = 0;

	QList<QByteArray> rows = mapData.split('\n');
	log (QString::number(rows.size()));
	for (QByteArray line : rows) {
		int length = 0;
		log ("ROW");
		QVector<char> buffer;
		for (char cell : line) {
			buffer.push_back(cell);
			length++;
		}
		if (length > m_mapSizeHorz) m_mapSizeHorz = length;
		m_map.push_back(buffer);
		m_mapSizeVert++;
	}
}

void MapWorker::updatePlayerPosition(int x, int y)
{
	m_currentPlayerPositionX = x;
	m_currentPlayerPositionY = y;

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
