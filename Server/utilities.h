#ifndef UTILITIES_H
#define UTILITIES_H

#include <QByteArray>
#include <QString>
#include <QRandomGenerator>

#include <tuple>

struct position
{
	int x;
	int y;
	position() {}
	position(int newX, int newY) { x = newX; y = newY; }
	bool operator<( const position& other) const {
			 return std::tie(x,y) < std::tie(other.x,other.y);
		}
	bool operator==( const position& other) const {
			 return std::tie(x,y) == std::tie(other.x,other.y);
		}
};

enum playerMovements {
	sup,
	sdown,
	sleft,
	sright
};

enum actions {
	open,
	close,
	pick,
	drop,
	push,
    kick,
    pull
};

class Utilities
{
public:
	static QByteArray generateId();
	static position getCoordsBySide (position pos, playerMovements side);
	static playerMovements getSideFromString(QString side);
};

#endif // UTILITIES_H
