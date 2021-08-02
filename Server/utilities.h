#ifndef UTILITIES_H
#define UTILITIES_H

#include <QByteArray>
#include <QString>
#include <QRandomGenerator>

#include "enums.h"

class Utilities
{
public:
	static QByteArray generateId();
	static position getCoordsBySide (position pos, playerMovements side);
	static playerMovements getSideFromString(QString side);
};

#endif // UTILITIES_H
