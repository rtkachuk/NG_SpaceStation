#ifndef ITEMCONTROLLER_H
#define ITEMCONTROLLER_H

#include <QVector>
#include <QMap>
#include <QFile>
#include <QDebug>

#include "utilities.h"

class ItemController
{
public:
    ItemController();

	void addItem(position cords, QByteArray id);
	void deleteItem(position cords, QByteArray id);
	void loadItems();

    QByteArray getItemIdByPos(position cords);
    QByteArray getItemIdByPos(position cords, int elementNumber);
	QMap<position, QVector<QByteArray>>* getItems() { return &m_ids; }

private:
	void parseItem(QString line);
	void log(QString msg);
	QMap<position, QVector<QByteArray>> m_ids;
	int m_amountOfItems;
};

#endif // ITEMCONTROLLER_H
