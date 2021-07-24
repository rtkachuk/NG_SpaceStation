#ifndef ITEMLOADER_H
#define ITEMLOADER_H

#include <QObject>
#include <QDebug>
#include <QVector>
#include <QFile>

#include "baseitem.h"
#include "baseweapon.h"
#include "basetool.h"

class ItemLoader : public QObject
{
	Q_OBJECT
public:
	ItemLoader();
	void loadItems();
	BaseTool parseTool(QString line);
	BaseWeapon parseWeapon(QString line);
	BaseTool getToolById(QByteArray id);
	BaseWeapon getWeaponById(QByteArray id);
	bool checkIdExist(QByteArray id);

private:
	void log(QString msg);


	QVector<BaseTool> m_tools;
	QVector<BaseWeapon> m_weapons;
	QString m_data;
	int m_amountOfItems;
};

#endif // ITEMLOADER_H
