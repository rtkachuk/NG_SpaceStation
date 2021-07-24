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

    void addItem(position cords, QByteArray id) { m_ids[cords] = id; }
    void deleteItem(position cords) { m_ids.remove(cords); }

	void loadItems();

    QByteArray getItem(position cords);

private:
	void parseItem(QString line);
	void log(QString msg);

    QMap<position, QByteArray> m_ids;
	int m_amountOfItems;
};

#endif // ITEMCONTROLLER_H
