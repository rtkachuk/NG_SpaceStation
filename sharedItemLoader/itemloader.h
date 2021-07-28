#ifndef ITEMLOADER_H
#define ITEMLOADER_H

#include <QObject>
#include <QDebug>
#include <QVector>
#include <QFile>

#include "baseitem.h"

class ItemLoader : public QObject
{
	Q_OBJECT
public:
	ItemLoader();
	void loadItems();
	BaseItem parseItem(QString line);
	BaseItem getItemById(QByteArray id);
	QByteArray getIdByName(QString name);
	bool checkIdExist(QByteArray id);

private:
	void log(QString msg);


	QVector<BaseItem> m_items;
	QString m_data;
	int m_amountOfItems;
};

#endif // ITEMLOADER_H
