#include "mapworker.h"

MapWorker::MapWorker()
{
	for (int current=1; current<6; current++)
		m_spacePixmaps.push_back(":/misc/space" + QString::number(current) + ".png");
}

void MapWorker::mapInit(QByteArray mapData)
{
	m_map.clear();

	m_mapSizeHorz = 0;
	m_mapSizeVert = 0;

	QList<QByteArray> rows = mapData.split('\n');
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
		if (side)
			m_player->setPixmap(QPixmap(":/players/fox_left.png"));
		else
			m_player->setPixmap(QPixmap(":/players/fox_right.png"));
		side = !side;

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

void MapWorker::placeItem(ItemInfo itemInfo)
{
	BaseItem tool = m_itemLoader->getItemById(itemInfo.id);

	QPixmap image;

	if (tool.getId() != "-1") {
		image = QPixmap(":" + tool.getPixmap());
	}

	QGraphicsPixmapItem *item = m_scene->addPixmap(image);
	item->setPos(itemInfo.pos.x * m_cellSizePixels, itemInfo.pos.y * m_cellSizePixels);

	if (m_items.contains(itemInfo))
		m_items[itemInfo].push_back(item);
	else {
		QVector<QGraphicsPixmapItem*> items;
		items.push_back(item);
		m_items[itemInfo] = items;
	}
}

void MapWorker::removeItem(ItemInfo item)
{
	QGraphicsPixmapItem *pixm = m_items[item].first();
	if (pixm != nullptr) {
		m_scene->removeItem(pixm);
		log ("Removed item " + item.id);
	}
	else
		log ("Map items data contains no objects!");
	m_items[item].removeOne(pixm);

	if (m_items[item].isEmpty())
		m_items.remove(item);
}

void MapWorker::constructCell(int x, int y, QString imagePath)
{
	m_scene->addPixmap(imagePath)->setPos(x, y);
}

void MapWorker::updateCell(int x, int y, char object)
{
	switch (object) {
		case '.': constructCell(x, y, ":/buildings/floor.png"); break;
		case '_': constructCell(x, y, ":/buildings/floor1.png"); break;
		case '#': constructCell(x, y, ":/buildings/wall.png"); break;
		case 'o': constructCell(x, y, ":/buildings/door_open.png"); break;
		case 'c': constructCell(x, y, ":/buildings/door_closed.png"); break;
		case 'b': constructCell(x, y, ":/buildings/door_broken.png"); break;
		case '*': m_scene->addPixmap(selectSpacePixmap())->setPos(x, y); break;
		case '~': constructCell(x, y, ":/buildings/foundation.png"); break;
		default: m_scene->addRect(x, y, m_cellSizePixels, m_cellSizePixels);
	}
}

QPixmap MapWorker::selectSpacePixmap()
{
	return QPixmap(m_spacePixmaps[m_randomGenerator.bounded(1, 5)]);
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
	m_player = m_scene->addPixmap(QPixmap(":/players/fox_left.png"));
	m_player->setPos(m_currentPlayerPositionX * m_cellSizePixels, m_currentPlayerPositionY * m_cellSizePixels);
	m_player->setZValue(10);
}

void MapWorker::log(QString message)
{
	qDebug() << "[MapWorker]: " << message;
}
