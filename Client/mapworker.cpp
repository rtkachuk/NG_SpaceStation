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
		QVector<char> buffer;
		for (char cell : line) {
			buffer.push_back(cell);
			length++;
		}
		if (length > m_mapSizeHorz) m_mapSizeHorz = length;
		m_map.push_back(buffer);
		m_mapSizeVert++;
	}

	m_scene->setSceneRect(0, 0, m_mapSizeHorz * m_cellSizePixels, m_mapSizeVert * m_cellSizePixels);
}

void MapWorker::removePlayer(QByteArray id)
{
	delete m_players[id];
	m_players.erase(m_players.find(id));
}

void MapWorker::updatePlayerPosition(QByteArray id, int x, int y)
{
	if (id == m_playerId) {
		m_currentPlayerPositionX = x;
		m_currentPlayerPositionY = y;
		m_player->setPos(m_currentPlayerPositionX * m_cellSizePixels, m_currentPlayerPositionY * m_cellSizePixels);
	} else {
		if (m_players.contains(id)) {
			m_players[id]->setPos(x * m_cellSizePixels, y * m_cellSizePixels);
		} else {
			m_players[id] = m_scene->addPixmap(QPixmap(":/players/player1.png"));
			m_players[id]->setZValue(10);
		}
	}
}

void MapWorker::updateMap(int x, int y, char object)
{
	m_map[y][x] = object;
	QTransform deviceTransform;
	QGraphicsItem *item = m_scene->itemAt(x * m_cellSizePixels, y * m_cellSizePixels, deviceTransform);
	delete item;
	updateCell(x * m_cellSizePixels, y * m_cellSizePixels, object);
}

void MapWorker::updateCell(int x, int y, char object)
{
	if (object != ' ') // it's not space
		m_scene->addPixmap(QPixmap(":/buildings/floor.png"))->setPos(x, y);
	switch (object) {
		case '.': m_scene->addPixmap(QPixmap(":/buildings/floor.png"))->setPos(x, y); break;
		case '#': m_scene->addPixmap(QPixmap(":/buildings/wall.png"))->setPos(x, y); break;
		case 'o': m_scene->addPixmap(QPixmap(":/buildings/door_open.png"))->setPos(x, y); break;
		case 'c': m_scene->addPixmap(QPixmap(":/buildings/door_closed.png"))->setPos(x, y); break;
		case 'b': m_scene->addPixmap(QPixmap(":/buildings/door_broken.png"))->setPos(x, y); break;
		case 't': m_scene->addPixmap(QPixmap(":/furniture/trash_can.png"))->setPos(x, y); break;
		case 'T': m_scene->addPixmap(QPixmap(":/furniture/trash_can_open.png"))->setPos(x, y); break;
		case 's': m_scene->addPixmap(QPixmap(":/furniture/box.png"))->setPos(x, y); break;
		case 'S': m_scene->addPixmap(QPixmap(":/furniture/open_box.png"))->setPos(x, y); break;
		case 'r': { QGraphicsPixmapItem *item = m_scene->addPixmap(QPixmap(":/tech/server_rack_kvm.png")); item->setPos(x, y); item->setZValue(10); } break;
		case 'R': { QGraphicsPixmapItem *item = m_scene->addPixmap(QPixmap(":/tech/server_rack_kvm_switch.png")); item->setPos(x, y); item->setZValue(10); } break;
		default: m_scene->addRect(x, y, m_cellSizePixels, m_cellSizePixels);
	}
}

void MapWorker::drawMap()
{
	int currentY = 0;
	int currentX = 0;
	for (QVector<char> row : m_map) {
		for (char cell : row) {
			updateCell(currentX, currentY, cell);
			currentX += m_cellSizePixels;
		}
		currentX = 0;
		currentY += m_cellSizePixels;
	}
	m_player = m_scene->addPixmap(QPixmap(":/players/player.png"));
	m_player->setPos(m_currentPlayerPositionX * m_cellSizePixels, m_currentPlayerPositionY * m_cellSizePixels);
	m_player->setZValue(10);
}

void MapWorker::log(QString message)
{
	qDebug() << "[MapWorker]: " << message;
}
