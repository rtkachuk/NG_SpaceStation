#ifndef ENUMS_H
#define ENUMS_H

#include <tuple>

struct position
{
    int x;
    int y;
	bool operator<( const position& other) const {
			 return std::tie(x,y) < std::tie(other.x,other.y);
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
    push
};

#endif // ENUMS_H
