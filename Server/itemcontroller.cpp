#include "itemcontroller.h"

ItemController::ItemController()
{
	loadItems();
}

void ItemController::addItem(position cords, QByteArray id)
{
	m_ids[cords].push_back(id);
}

void ItemController::deleteItem(position cords, QByteArray id)
{
	if (m_ids.contains(cords))
		m_ids[cords].removeOne(id);
	if (m_ids[cords].size() == 0)
		m_ids.remove(cords);
}

void ItemController::loadItems()
{
	m_amountOfItems = 0;
	QFile file("itemPositions.txt");

	if (file.open(QIODevice::ReadOnly) == false) {
		log ("Failed to open itemPositions.txt");
		return;
	}

	while (file.atEnd() == false)
		parseItem(file.readLine());

	file.close();
	log ("Placed " + QString::number(m_amountOfItems) + " items!");
}

QByteArray ItemController::getItemIdByPos(position cords)
{
	return getItemIdByPos(cords, 0);
}

QByteArray ItemController::getItemIdByPos(position cords, int elementNumber)
{
	if (m_ids.contains(cords))
		if (m_ids[cords].size() > elementNumber)
			return m_ids[cords].at(elementNumber);
	return "";
}

void ItemController::parseItem(QString line)
{
	QList<QString> itemPrefs = line.split(':');

	position pos;
	pos.x = itemPrefs[1].toInt();
	pos.y = itemPrefs[2].toInt()-1;

	addItem(pos, itemPrefs[0].toUtf8());
	m_amountOfItems++;
}

void ItemController::log(QString msg)
{
	qDebug() << "[ItemController]: " << msg;
}
