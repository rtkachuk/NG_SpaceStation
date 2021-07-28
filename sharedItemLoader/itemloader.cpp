#include "itemloader.h"

ItemLoader::ItemLoader()
{

}

void ItemLoader::loadItems()
{
	QFile itemFile("items.txt");

	if (itemFile.open(QIODevice::ReadOnly) == false) {
		log ("Error opening file: " + itemFile.errorString());
		return;
	}

	m_amountOfItems = 0;
	m_items.clear();

	while (itemFile.atEnd() == false) {
		QString line = itemFile.readLine();
		m_items.push_back(parseItem(line));
	}

	itemFile.close();

	log ("Loaded " + QString::number(m_amountOfItems) + " items");
}

BaseItem ItemLoader::parseItem(QString line)
{
	QList<QString> paramethers = line.split(':');
	BaseItem bufferItem;

	itemType type = itemType::notype;
	if (paramethers[0] == "tool") type = itemType::tool;
	if (paramethers[0] == "weapon") type = itemType::weapon;

	bufferItem.setType(type);
	bufferItem.setName(paramethers[1]);
	bufferItem.setWearableMode(BaseItem::detectPlayerWearable(paramethers[2]));
	bufferItem.setToolMode(BaseItem::detectToolMode(paramethers[3]));
	bufferItem.setWeaponMode(BaseItem::detectWeaponMode(paramethers[4]));
	bufferItem.setDamage(paramethers[5].toInt());
	bufferItem.setPixmap(paramethers[6]);
	bufferItem.setDescription(paramethers[7]);
	bufferItem.setId(QByteArray::number(m_amountOfItems+1));

	log ("=============================");
	log ("Item name: " + bufferItem.getName());
	log ("Item pixmap: " + bufferItem.getPixmap());

	m_amountOfItems++;

	log ("Loaded item: " + bufferItem.getName());

	return bufferItem;
}

BaseItem ItemLoader::getItemById(QByteArray id)
{
	for (BaseItem tool : m_items) {
		if (tool.getId() == id)
			return tool;
	}

	return BaseItem();
}

QByteArray ItemLoader::getIdByName(QString name)
{
	for (BaseItem tool : m_items)
		if (tool.getName() == name)
			return tool.getId();
	return "";
}

bool ItemLoader::checkIdExist(QByteArray id)
{
	if (getItemById(id).getId() != "-1")
		return true;
	return false;
}

void ItemLoader::log(QString msg)
{
	qDebug() << "[ItemLoader]: " << msg;
}
