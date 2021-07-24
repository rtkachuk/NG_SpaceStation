#ifndef ITEMCONTROLLER_H
#define ITEMCONTROLLER_H

#include <QVector>
#include <QMap>

#include "enums.h"

class ItemController
{
public:
    ItemController();

    void addItem(position cords, QByteArray id) { m_ids[cords] = id; }
    void deleteItem(position cords) { m_ids.remove(cords); }

    QByteArray getItem(position cords);

private:
    QMap<position, QByteArray> m_ids;
};

#endif // ITEMCONTROLLER_H
