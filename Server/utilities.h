#ifndef UTILITIES_H
#define UTILITIES_H

#include <QByteArray>
#include <QRandomGenerator>

#include "enums.h"

class Utilities
{
public:
	static QByteArray generateId();
	static position getCoordsBySide (position pos, playerMovements side);
};

#endif // UTILITIES_H
