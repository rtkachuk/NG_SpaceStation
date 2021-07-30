#ifndef PLAYERWEAR_H
#define PLAYERWEAR_H

#include <QByteArray>
#include <QMap>
#include "enums.h"
#include "../sharedItemLoader/itemloader.h"

class PlayerWear
{
public:

	PlayerWear();
	PlayerWear(ItemLoader *loader);

	QByteArray getwear(playerWearable place) { return m_wears[place]; }
	QByteArray wearOn(QByteArray id) { m_wears[detectPlace(id)] = id; return "WEAR:" + id + ":" + detectPlace(id) + "|";}
	QByteArray takeOff(QByteArray id) { m_wears[detectPlace(id)] = ""; return "TAKEOFF:" + id + "|";}

private:

	playerWearable detectPlace(QByteArray id) { return m_loader->getItemById(id).getWearableMode(); }
	void log(QString msg);

	QMap<int, QByteArray> m_wears;

	ItemLoader* m_loader;
};

#endif // PLAYERWEAR_H
