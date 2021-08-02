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
	if (paramethers[1] == "tool") type = itemType::tool;
	if (paramethers[1] == "weapon") type = itemType::weapon;
	if (paramethers[1] == "furniture") type = itemType::furniture;

	bufferItem.setId(paramethers[0].toUtf8());
	bufferItem.setType(type);
	bufferItem.setName(paramethers[2]);
	bufferItem.setWearableMode(BaseItem::detectPlayerWearable(paramethers[3]));
	bufferItem.setToolMode(BaseItem::detectToolMode(paramethers[4]));
	bufferItem.setWeaponMode(BaseItem::detectWeaponMode(paramethers[5]));
	bufferItem.setDamage(paramethers[6].toInt());
	bufferItem.setPixmap(paramethers[7]);
	bufferItem.setDescription(paramethers[8]);

	log ("=============================");
	log ("Item name: " + bufferItem.getName());
	log ("Item pixmap: " + bufferItem.getPixmap());
	log ("Item id: " + bufferItem.getId());

	m_amountOfItems++;


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
