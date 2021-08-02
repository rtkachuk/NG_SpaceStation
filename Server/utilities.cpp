#include "utilities.h"

QByteArray Utilities::generateId()
{
	QByteArray possibleChars("0123456789");
	int randomStringLength = 6;
	QByteArray id;

	for (int symbol = 0; symbol < randomStringLength; symbol++) {
		id += possibleChars.at(QRandomGenerator::global()->generate() % randomStringLength);
	}
	return id;
}

position Utilities::getCoordsBySide(position pos, playerMovements side)
{
	position result = pos;
	switch (side) {
		case playerMovements::sup: result.y--; break;
		case playerMovements::sdown: result.y++; break;
		case playerMovements::sleft: result.x--; break;
		case playerMovements::sright: result.x++; break;
	}

	return result;
}
