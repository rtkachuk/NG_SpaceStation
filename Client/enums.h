#ifndef ENUMS_H
#define ENUMS_H

#include <QByteArray>
#include <QObject>
#include <iostream>

enum playerMovement {
	moveUp,
	moveDown,
	moveLeft,
	moveRight
};

struct position {
	int x;
	int y;
    position() {}
    position(int newX, int newY) { x = newX; y = newY; }
	bool operator<( const position& other) const {
			 return std::tie(x,y) < std::tie(other.x,other.y);
		}
};

struct ItemInfo {
	position pos;
	QByteArray id;
	bool operator<( const ItemInfo& other) const {
			 return std::tie(pos, id) < std::tie(other.pos,other.id);
		}
};

Q_DECLARE_METATYPE(ItemInfo);
Q_DECLARE_METATYPE(position);

#endif // ENUMS_H
