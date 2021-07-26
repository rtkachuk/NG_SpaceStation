#ifndef ENUMS_H
#define ENUMS_H

#include <QByteArray>

enum playerMovement {
	moveUp,
	moveDown,
	moveLeft,
	moveRight
};

struct position {
	int x;
	int y;
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

#endif // ENUMS_H
