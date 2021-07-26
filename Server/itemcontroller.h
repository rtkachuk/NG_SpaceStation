#ifndef ITEMCONTROLLER_H
#define ITEMCONTROLLER_H

#include <QVector>
#include <QMap>
#include <QFile>
#include <QDebug>

#include "enums.h"

class ItemController
{
public:
    ItemController();

	void addItem(position cords, QByteArray id) { m_ids[cords].push_back(id); }
	void deleteItem(position cords, QByteArray id) { m_ids[cords].removeOne(id); }

	void loadItems();

    QByteArray getItem(position cords);
	QMap<position, QVector<QByteArray>>* getItems() { return &m_ids; }

private:
	void parseItem(QString line);
	void log(QString msg);

	QMap<position, QVector<QByteArray>> m_ids;
	int m_amountOfItems;
};

#endif // ITEMCONTROLLER_H
