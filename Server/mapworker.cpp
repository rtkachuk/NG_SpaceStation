#include "mapworker.h"

MapWorker::MapWorker(ItemLoader *loader, HealthControl *health)
{
	m_itemController = new ItemController();
	m_itemLoader = loader;
	m_healthController = health;
	m_electricityController = new ElectricityController(this);

	connect (m_electricityController, &ElectricityController::updateGeneratorState, this, &MapWorker::generatorStateChanged);
	connect (m_electricityController, &ElectricityController::updateNodeState, this, &MapWorker::nodeStateChanged);
	connect (m_electricityController, &ElectricityController::generatorExploded, this, &MapWorker::explode);
}

void MapWorker::processMap(QByteArray mapData)
{
	m_mapData = mapData;
	m_map.clear();

	QList<QByteArray> rows = mapData.split('\n');
	for (QByteArray line : rows) {
		int length = 0;
		QVector<char> buffer;
		for (char cell : line) {
			buffer.push_back(cell);
			length++;
		}
		m_map.push_back(buffer);
	}

	log ("Map loading done! (" + QByteArray::number(mapData.size()) + " bytes)");
}

void MapWorker::processPlayerPush(QTcpSocket *buffer, actions act, QString direction)
{
	playerMovements side = Utilities::getSideFromString(direction);
	position pos= Utilities::getCoordsBySide(m_playerPositions[buffer],side);
	if (act == actions::push){
		pushPlayer(side,buffer);
		processItemPush(pos,buffer,side);
	}
}

void MapWorker::processItemPush(position pos, QTcpSocket *socket, playerMovements side)
{
	int itemNumber = 0;
	itemType type = itemType::notype;
	QByteArray id;

	do {
		id = m_itemController->getItemIdByPos(pos, itemNumber);
		if (id.isEmpty())
			return;
		type = m_itemLoader->getItemById(id).getType();
		itemNumber++;
	} while (type != itemType::furniture);

	position pushes = m_playerPositions[socket];
	position itemToPushCords=Utilities::getCoordsBySide(pushes,side);
	position newPosItemToPush=Utilities::getCoordsBySide(itemToPushCords,side);

	if (isThereAFurniture(newPosItemToPush)) return;
	if (isThereAWall(newPosItemToPush)) return; // We found wall

	m_itemController->deleteItem(itemToPushCords,id);
	emit sendToAll("ICLEAR:" + QByteArray::number(itemToPushCords.x) + ":" + QByteArray::number(itemToPushCords.y) + ":" + id + "|");
	m_itemController->addItem(Utilities::getCoordsBySide(itemToPushCords,side),id);
	emit sendToAll("IPLACE:" + QByteArray::number(newPosItemToPush.x) + ":" + QByteArray::number(newPosItemToPush.y) + ":" + id + "|");
}

void MapWorker::processPlayerKick(QTcpSocket *buffer, QString direction)
{
	playerMovements side = Utilities::getSideFromString(direction);
	position playerToPushCords=Utilities::getCoordsBySide(m_playerPositions[buffer],side);
	QTcpSocket *playerToPush=getPlayerByPosition(playerToPushCords);

	if (playerToPush == nullptr) return;

	QByteArray id=m_inventoryController->getWear(playerWearable::holdable, buffer);

	int damage=1;
	if(id.isEmpty()==false){
		damage=m_itemLoader->getItemById(id).getDamage();
	}

	m_healthController->makeDamage(playerToPush,damage);
	m_itemController->addItem(playerToPushCords, "24"); // blood id
	emit sendToPlayer(playerToPush, "HEALTH:" + QByteArray::number(m_healthController->getHealth(playerToPush)) + "|");
	emit sendToAll("IPLACE:" + QByteArray::number(playerToPushCords.x) + ":" + QByteArray::number(playerToPushCords.y) + ":24|");
	pushPlayer(side,buffer);
}
bool MapWorker::checkMovementPosition(position pos)
{
	bool conditionIsFloor =
			m_map[pos.y][pos.x] == '.' ||
			m_map[pos.y][pos.x] == 'o' ||
			(m_map[pos.y][pos.x] >= '1' && m_map[pos.y][pos.x] <= '9') ||
			m_map[pos.y][pos.x] == '!' ||
			m_map[pos.y][pos.x] == '@' ||
			m_map[pos.y][pos.x] == '~';

	bool conditionNoItemsOnTheWay = m_itemLoader->getItemById(m_itemController->getItemIdByPos(pos)).getType() != itemType::furniture;

	return conditionIsFloor && conditionNoItemsOnTheWay;
}

QTcpSocket *MapWorker::getPlayerByPosition(position pos)
{
	for(QTcpSocket* buffer : m_playerPositions.keys()){
		if(m_playerPositions[buffer].x==pos.x && m_playerPositions[buffer].y==pos.y){
			return buffer;
		}
	}
	return nullptr;
}

void MapWorker::pushPlayer(playerMovements side, QTcpSocket* buffer)
{
	if(buffer==nullptr) return;

	position pushes = m_playerPositions[buffer];
	position playerToPushCords=Utilities::getCoordsBySide(pushes,side);
	QTcpSocket *playerToPush=getPlayerByPosition(playerToPushCords);
	if (playerToPush == nullptr) return;
	movePlayer(playerToPush, side);
}

void MapWorker::addUser(QTcpSocket *socket, position pos)
{
	m_playerPositions[socket] = pos;
	m_playerIds[socket] = Utilities::generateId();
}

void MapWorker::movePlayer(QTcpSocket *socket, playerMovements side)
{
	position pos = m_playerPositions[socket];

	switch (side) {
		case playerMovements::sup: pos.y--; break;
		case playerMovements::sdown: pos.y++; break;
		case playerMovements::sleft: pos.x--; break;
		case playerMovements::sright: pos.x++; break;
		default: log ("Unknown side passed to movePlayer");
	}

	processPlayerMovement(pos, socket);
}

void MapWorker::updatePlayerPos(QTcpSocket* socket, position pos)
{
	m_playerPositions[socket] = pos;
}

void MapWorker::processPlayerAction(QTcpSocket *socket, actions act, QString direction)
{
	position pos = m_playerPositions[socket];
	playerMovements side = Utilities::getSideFromString(direction);
	position actPos = Utilities::getCoordsBySide(pos, side);

	switch (act) {
		case actions::open: formatMapChange(actPos, processOpen(actPos)); break;
		case actions::close: formatMapChange(actPos, processClose(actPos)); break;
		default: log("Unknown action passed to processPlayerAction function");
	}
}

void MapWorker::processPlayerMovement(position pos, QTcpSocket *socket)
{
	if (checkMovementPosition(pos)) {
		updatePlayerPos(socket, pos);
		emit sendToAll(formatResponce(pos, socket));
	}
}

void MapWorker::updateMapData(position pos, char object)
{
	int offset = 0;
	for (int row=0; row<pos.y; row++) {
		offset += m_map[row].size() + 1;
	}
	offset += pos.x;
	m_mapData[offset] = object;
}

void MapWorker::formatMapChange(position pos, char object)
{
	if (m_map[pos.y][pos.x] == object) {
		return;
	}

	m_map[pos.y][pos.x] = object;
	updateMapData(pos, object);
	emit sendToAll(QByteArray("CHG:" + QByteArray::number(pos.x) + ":" + QByteArray::number(pos.y) + ":" + object + "|"));

	if (object == '~') // If foundation should be placed
	{
		if (m_electricityController->checkWireExist(pos)) {
			emit sendToAll("IPLACE:" + QByteArray::number(pos.x) + ":" + QByteArray::number(pos.y) + ":41|"); // Place wire
		}
	}
}

QByteArray MapWorker::formatResponce(position pos, QTcpSocket *socket)
{
	return "POS:" + m_playerIds[socket] + ":" + QByteArray::number(pos.x) + ":" + QByteArray::number(pos.y) + "|";
}

char MapWorker::processOpen(position pos)
{
	switch(m_map[pos.y][pos.x]) {
		case 'c': return 'o';
		case 't': return 'T';
		case 's': return 'S';
		default: return m_map[pos.y][pos.x];
	}
}

char MapWorker::processClose(position pos)
{
	switch(m_map[pos.y][pos.x]) {
		case 'o': return 'c';
		case 'T': return 't';
		case 'S': return 's';
		default: return m_map[pos.y][pos.x];
	}
}

bool MapWorker::isThereAWall(position pos)
{
	return m_map.at(pos.y).at(pos.x) == '#'; // We found wall
}

bool MapWorker::isThereAFurniture(position pos)
{
	int itemNumber = 0;
	itemType type = itemType::notype;
	QByteArray id;

	do {
		id = m_itemController->getItemIdByPos(pos, itemNumber);
		if (id.isEmpty() == false) {
			type = m_itemLoader->getItemById(id).getType();
			if (type == itemType::furniture)
				return true;
			itemNumber++;
		}
	} while (id.isEmpty() == false);
	return false;
}

void MapWorker::processDrop(QTcpSocket *socket, QByteArray data, QByteArray bside)
{
	position pos = m_playerPositions[socket];
	playerMovements side = Utilities::getSideFromString(bside);
	position actPos = Utilities::getCoordsBySide(pos, side);
	return dropItem(data, actPos, socket);
}

void MapWorker::processPick(QTcpSocket *socket, QString data)
{
	position pos = m_playerPositions[socket];
	playerMovements side = Utilities::getSideFromString(data);
	position actPos = Utilities::getCoordsBySide(pos, side);

	pickItem(actPos, socket);
}

void MapWorker::pickItem(position pos, QTcpSocket *player)
{
	int itemNumber = 0;
	itemType type = itemType::notype;
	QByteArray id;
	do {
		id = m_itemController->getItemIdByPos(pos, itemNumber);

		if (id.isEmpty())
			break;

		type = m_itemLoader->getItemById(id).getType();
		itemNumber++;
	} while (type == itemType::furniture);

	if (id.isEmpty() == false && type != itemType::furniture && type != itemType::notype) {
		m_inventoryController->addItemToInventory(player, id);
		m_itemController->deleteItem(pos, id);
		emit sendToPlayer(player, "PITEM:" + id + "|");
		emit sendToAll("ICLEAR:" + QByteArray::number(pos.x) + ":" + QByteArray::number(pos.y) + ":" + id + "|");
	}
}

void MapWorker::dropItem(QByteArray id, position pos, QTcpSocket *player)
{
	if (id.isEmpty() == false && m_itemLoader->checkIdExist(id)) {
		m_inventoryController->removeItemFromInventory(player, id);
		m_itemController->addItem(pos, id);
		emit sendToPlayer(player, "DITEM:" + id + "|");
		emit sendToAll("IPLACE:" + QByteArray::number(pos.x) + ":" + QByteArray::number(pos.y) + ":" + id + "|");
		m_inventoryController->takeOff(id, player);
	}
}

void MapWorker::processDestroy(QTcpSocket *player, QByteArray side)
{
	QByteArray itemInHands = m_inventoryController->getWear(playerWearable::holdable, player);
	position pos = Utilities::getCoordsBySide(m_playerPositions[player], Utilities::getSideFromString(side));

	position playerPos = m_playerPositions[player];
	log (QString::number(playerPos.y) + ":::" + QString::number(playerPos.x));
	log (QString::number(pos.y) + ":::" + QString::number(pos.x));

	// Hardcoded big_hammer. NEED TO BE FIXED WITH RECIPES LOADER!!!
	//

	if (itemInHands == "25") {
		destroyElementFromMap(pos);
	}
}

void MapWorker::processBuild(QTcpSocket *player, QByteArray direction, QByteArray id)
{
	playerMovements side = Utilities::getSideFromString(direction);
	position pos = Utilities::getCoordsBySide(m_playerPositions[player], side);

	if (checkBuildRequirementsMet(player, id)) {
		getResourcesFromPlayerForBuilding(player, id);
		buildElementOnMap(pos, id);
	}
}

bool MapWorker::checkBuildRequirementsMet(QTcpSocket *player, QByteArray id)
{
	QMap<QByteArray, int> requirements = m_inventoryController->getRequirementsForCraftingTable(id);
	QList<QByteArray> keys = requirements.keys();
	for (QByteArray element : keys) {
		if (requirements[element] > m_inventoryController->getItemsAmountInInventory(player, element))
			return false;
	}
	return true;
}

void MapWorker::getResourcesFromPlayerForBuilding(QTcpSocket *player, QByteArray id)
{
	QMap<QByteArray, int> requirements = m_inventoryController->getRequirementsForCraftingTable(id);
	QList<QByteArray> keys = requirements.keys();
	for (QByteArray element : keys) {
		int amount = requirements[element];
		for (int i=0; i<amount; i++) {
			m_inventoryController->removeItemFromInventory(player, element);
			emit sendToPlayer(player, "DITEM:" + element + "|");
		}
	}
}

void MapWorker::destroyElementFromMap(position pos)
{
	QByteArray element = m_itemController->getItemIdByPos(pos);

	if (element.isEmpty()) {
		char building = m_map[pos.y][pos.x];
		switch (building) {
			case '#': element = "WALL"; formatMapChange(pos, '~'); break;
			case '.': element = "FLOOR"; formatMapChange(pos, '~'); break;
		}
	} else {
		m_itemController->deleteItem(pos, element);
		emit sendToAll("ICLEAR:" + QByteArray::number(pos.x) + ":" + QByteArray::number(pos.y) + ":" + element + "|");
	}

	QVector<QByteArray> requirements = m_inventoryController->getRequirementsForCraftingRaw(element);
	log (QString::number(requirements.size()));
	for (QByteArray id : requirements) {
		m_itemController->addItem(pos, id);
		emit sendToAll("IPLACE:" + QByteArray::number(pos.x) + ":" + QByteArray::number(pos.y) + ":" + id + "|");
	}
}

void MapWorker::buildElementOnMap(position pos, QByteArray element)
{
	if (element == "WALL")
		formatMapChange(pos, '#');
	if (element == "FLOOR")
		formatMapChange(pos, '.');
}

void MapWorker::startDynamite(QTcpSocket *client, QString direction)
{
	position playerPos = m_playerPositions[client];
	position side = Utilities::getCoordsBySide(playerPos, Utilities::getSideFromString(direction));
	dropItem("27", side, client);

	log ("Sleeping...");
	QTimer::singleShot(10000, this, std::bind(&MapWorker::explode, this, side, 7));
	log ("BOOOM");
}

void MapWorker::sendElectricToolsStatuses(QTcpSocket *client)
{
	sendToPlayer(client, m_electricityController->getNewPlayerInfo());
}

void MapWorker::processUseAction(QTcpSocket *client, QString side)
{
	position pos = Utilities::getCoordsBySide(m_playerPositions[client], Utilities::getSideFromString(side));

	switch (m_electricityController->getObjectByCords(pos)) {
		case electricityObjectType::generator: emit sendToPlayer(client, m_electricityController->getGeneratorStatus(pos)); break;
		case electricityObjectType::node: m_electricityController->switchNode(pos); break;
		default: log ("No electricity objects found!");
	}
}

void MapWorker::processGeneratorChangeFromController(bool state, int power, position pos)
{
	switch (m_electricityController->getObjectByCords(pos)) {
		case electricityObjectType::generator: m_electricityController->setGeneratorConfiguration(state, power, pos); break;
		default: log ("No electricity objects found!");
	}
	log (QString::number(pos.x) + ":::" + QString::number(pos.y));
}

void MapWorker::explode(position pos, int radius)
{
	int x = pos.x;
	int y = pos.y;

	for (int i = x-radius; i<=x+radius; i++)
		for (int j=y-radius; j<=y+radius; j++)
			if ((i-x)*(i-x) + (j-y) * (j-y) <= radius*radius) {
				position exPos;
				exPos.x = i;
				exPos.y = j;
				explodeCell(exPos);
			}
}

void MapWorker::generatorStateChanged(position pos, QByteArray state)
{
	sendToAll("GEN:" + QByteArray::number(pos.x) + ":" + QByteArray::number(pos.y) + ":" + state + "|");
}

void MapWorker::nodeStateChanged(position pos, QByteArray state)
{
	sendToAll("NODE:" + QByteArray::number(pos.x) + ":" + QByteArray::number(pos.y) + ":" + state + "|");
}

void MapWorker::explodeCell(position pos)
{
	if (m_map[pos.y][pos.x] == '*') return;

	QByteArray element;
	do {
		element = m_itemController->getItemIdByPos(pos);
		if (element.isEmpty() == false) {
			m_itemController->deleteItem(pos, element);
			emit sendToAll("ICLEAR:" + QByteArray::number(pos.x) + ":" + QByteArray::number(pos.y) + ":" + element + "|");
			m_electricityController->clearCell(pos);
		}
	} while (element.isEmpty() == false);

	int number = m_randomGenerator.bounded(10);
	if (number > 7) { formatMapChange(pos, '*'); return; }
	if (number > 5) { formatMapChange(pos, '~'); return; }
}

void MapWorker::log(QString msg)
{
	qDebug() << "[MapWorker]: " << msg;
}
