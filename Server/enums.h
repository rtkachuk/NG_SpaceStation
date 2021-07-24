#ifndef ENUMS_H
#define ENUMS_H

struct position
{
    int x;
    int y;
};

enum playerMovements {
    sup,
    sdown,
    sleft,
    sright
};

enum actions {
    open,
    close
};

#endif // ENUMS_H
