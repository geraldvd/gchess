#include "operators.h"

Tile operator+(const Tile &t1, const Tile &t2)
{
    return Tile(t1.getPosition() + t2.getPosition());
}

bool operator==(const Tile &t1, const Tile &t2)
{
    return t1.getPosition()==t2.getPosition();
}

bool operator<(const Tile &t1, const Tile &t2)
{
    return t1.getPosition() < t2.getPosition();
}

bool operator>(const Tile &t1, const Tile &t2)
{
    return t1.getPosition() > t2.getPosition();
}

Move operator+(const Move &m, const unsigned int &i)
{
    return Move(m.getX() + i%8, m.getY() + (i-i%8)/8);
}

Move operator+(const unsigned int &i, const Move &m)
{
    return m+i;
}
