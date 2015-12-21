// Include standard libraries
#include <string>
#include <iomanip>

// Include project files
#include "operators.h"

// Specify namespaces
using namespace std;

Tile operator+(const Tile &t1, const Tile &t2)
{
    return Tile(t1.getPosition()+ t2.getPosition());
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


std::ostream &operator<<(std::ostream &os, Board *b)
{
    for(Tile *t : b->getTiles()) {
        if(t->isOccupied()) {
            os << setw(3) << t->getPiece()->getTypeString(true);
        } else {
            os << setw(3) << "-";
        }
        if(t->getX() == NUM_TILES_X-1) {
            os << endl;
        }
    }

    return os;
}
