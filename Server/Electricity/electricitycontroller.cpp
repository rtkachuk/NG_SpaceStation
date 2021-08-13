#include "electricitycontroller.h"

ElectricityController::ElectricityController(QObject *parent) : QObject(parent)
{
	loadMap();
}

void ElectricityController::addGenerator(position pos)
{
	ElectricGenerator *generator = new ElectricGenerator();
	m_generators[generator] = pos;
}

void ElectricityController::addNode(position pos)
{
	ElectricNode *node = new ElectricNode();
	m_nodes[pos] = node;
}

void ElectricityController::processElectricityLines()
{
	for (ElectricGenerator *generator : m_generators.keys()) {
		generator->setRequiredPower(inspectLine(m_generators[generator], position(0,0), generator->isWorking()));
	}
}

void ElectricityController::loadMap()
{
	QByteArray map;
	QFile mapFile("electricityMap.txt");

	if (mapFile.open(QIODevice::ReadOnly) == false) {
		log ("Error opening file: " + mapFile.errorString());
		return;
	}
	log ("Loaded map (" + QString::number(map.size()) + " bytes)");

	map = mapFile.readAll();
	mapFile.close();
	processMap(&map);
}

void ElectricityController::processMap(QByteArray *map)
{
	QList<QByteArray> rows = (*map).split('\n');
	int rowNumber = 0;
	for (QByteArray line : rows) {
		int length = 0;
		QVector<char> buffer;
		for (char cell : line) {
			buffer.push_back(cell);
			if (cell == 'g')
				addGenerator(position(rowNumber, length));
			if (cell == 'n')
				addNode(position(rowNumber, length));
			length++;
		}
		m_wireMap.push_back(buffer);
	}
}

int ElectricityController::inspectLine(position pos, position previous, bool powered)
{
	// Check here any technic exist
	updateNodeState(pos, powered);
	int powerRequired = 0;

	if (checkSideLine(position(pos.x + 1, pos.y), previous)) powerRequired+=inspectLine(position(pos.x + 1, pos.y), pos, powered);
	if (checkSideLine(position(pos.x - 1, pos.y), previous)) powerRequired+=inspectLine(position(pos.x - 1, pos.y), pos, powered);
	if (checkSideLine(position(pos.x, pos.y + 1), previous)) powerRequired+=inspectLine(position(pos.x, pos.y + 1), pos, powered);
	if (checkSideLine(position(pos.x, pos.y - 1), previous)) powerRequired+=inspectLine(position(pos.x, pos.y - 1), pos, powered);
	return powerRequired;
}

bool ElectricityController::checkSideLine(position pos, position previous)
{
	if (pos == previous) return false;
	return checkLineExist(pos);

}

bool ElectricityController::checkLineExist(position pos)
{
	char item = m_wireMap[pos.y][pos.x] ;
	if (item == 'w' || item == 'n')
		return true;
	return false;
}

void ElectricityController::updateNodeState(position pos, bool state)
{
	if (m_nodes.contains(pos)) {
		m_nodes[pos]->setPowered(state);
	}
}

void ElectricityController::log(QString msg)
{
	qDebug() << "[ElectricityController]: " << msg;
}
