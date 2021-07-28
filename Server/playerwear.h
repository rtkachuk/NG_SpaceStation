#ifndef PLAYERWEAR_H
#define PLAYERWEAR_H

#include <QByteArray>
#include "enums.h"
#include "../sharedItemLoader/itemloader.h"

class PlayerWear
{
public:
	PlayerWear(ItemLoader *loader);

	QByteArray getHead() { return m_head; }

private:

	QByteArray m_head;
	QByteArray m_hands;
	QByteArray m_torso;
	QByteArray m_legs;
	QByteArray m_feet;

	ItemLoader* m_loader;
};

#endif // PLAYERWEAR_H
