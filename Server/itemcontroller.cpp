#include "itemcontroller.h"

ItemController::ItemController()
{
	loadItems();
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

QByteArray ItemController::getItem(position cords)
{
    if(m_ids.contains(cords))
		return m_ids[cords].first();
    else
		return "";
}

void ItemController::parseItem(QString line)
{
	QList<QString> itemPrefs = line.split(':');

	position pos;
	pos.x = itemPrefs[1].toInt();
	pos.y = itemPrefs[2].toInt();

	addItem(pos, itemPrefs[0].toUtf8());
	m_amountOfItems++;
	log ("Placed item with id " + itemPrefs[0]);
}

void ItemController::log(QString msg)
{
	qDebug() << "[ItemController]: " << msg;
}
