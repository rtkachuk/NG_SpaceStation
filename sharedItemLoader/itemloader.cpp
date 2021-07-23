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

	while (itemFile.atEnd() == false) {
		QString line = itemFile.readLine();
		if (line.indexOf("tool") == 0)
			m_tools.push_back(parseTool(line));
		if (line.indexOf("weapon") == 0)
			m_weapons.push_back(parseWeapon(line));
	}

	itemFile.close();

	log ("Loaded " + QString::number(m_amountOfItems) + " items");
}

BaseTool ItemLoader::parseTool(QString line)
{
	QList<QString> paramethers = line.split(':');
	BaseTool bufferTool;
	bufferTool.setName(paramethers[1]);
	bufferTool.setWearableMode(BaseItem::detectPlayerWearable(paramethers[2]));
	bufferTool.setToolMode(BaseTool::detectToolMode(paramethers[3]));
	bufferTool.setDamage(paramethers[4].toInt());
	bufferTool.setDescription(paramethers[5]);
	bufferTool.setId(QByteArray::number(m_amountOfItems));

	m_amountOfItems++;

	log ("Loaded item: " + bufferTool.getName());

	return bufferTool;
}

BaseWeapon ItemLoader::parseWeapon(QString line)
{
	QList<QString> paramethers = line.split(':');
	BaseWeapon bufferWeapon;
	bufferWeapon.setName(paramethers[1]);
	bufferWeapon.setWearableMode(BaseItem::detectPlayerWearable(paramethers[2]));
	bufferWeapon.setWeaponMode(BaseWeapon::detectWeaponMode(paramethers[3]));
	bufferWeapon.setDamage(paramethers[4].toInt());
	bufferWeapon.setDescription(paramethers[5]);
	bufferWeapon.setId(QByteArray::number(m_amountOfItems));
	m_amountOfItems++;

	log ("Loaded weapon: " + bufferWeapon.getName());

	return bufferWeapon;
}

BaseTool ItemLoader::getToolById(QByteArray id)
{
	for (BaseTool tool : m_tools) {
		if (tool.getId() == id)
			return tool;
	}

	return BaseTool();
}

BaseWeapon ItemLoader::getWeaponById(QByteArray id)
{
	for (BaseWeapon weapon : m_weapons) {
		if (weapon.getId() == id)
			return weapon;
	}

	return BaseWeapon();
}

void ItemLoader::log(QString msg)
{
	qDebug() << "[ItemLoader]: " << msg;
}
