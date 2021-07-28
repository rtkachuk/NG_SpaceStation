#ifndef PLAYERWEAR_H
#define PLAYERWEAR_H

#include <QByteArray>
#include "enums.h"
#include "../sharedItemLoader/itemloader.h"

class PlayerWear
{
public:

	PlayerWear();
	PlayerWear(ItemLoader *loader);

	QByteArray getHead() { return m_head; }
	QByteArray wearOn(QByteArray id, playerWearable place) { if (m_loader->getItemById(id).getWearableMode() == place) return wearDressing(id, place); return ""; }
	QByteArray takeOff(playerWearable place) { return unwear (place); }

private:

	QByteArray wearDressing(QByteArray id, playerWearable place);
	QByteArray unwear(playerWearable place);
	void log(QString msg);

	QByteArray m_head;
	QByteArray m_hands;
	QByteArray m_torso;
	QByteArray m_legs;
	QByteArray m_feet;

	ItemLoader* m_loader;
};

#endif // PLAYERWEAR_H
