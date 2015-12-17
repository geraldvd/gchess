// Include standard library
#include <stdexcept>

// Include project files
#include "move.h"

// Specify namespaces
using namespace std;

Move::Move(const int &x, const int &y, const MoveType &mt) :
    move_type(mt)
{
    this->setX(x);
    this->setY(y);
}

int Move::getX() const
{
    return this->x;
}

int Move::getY() const
{
    return this->y;
}

MoveType Move::getMoveType() const
{
    return this->move_type;
}

void Move::setMoveType(const MoveType &mt)
{
    this->move_type = mt;
}

void Move::setX(const int &x)
{
    if(x>=-7 && x<8) {
        this->x = x;
    } else {
        // Invalid
        throw invalid_argument("x must be between -7 and 8");
    }
}

void Move::setY(const int &y)
{
    if(y>=-7 && y<8) {
        this->y = y;
    } else {
        // Invalid
        throw invalid_argument("y must be between -7 and 8");
    }
}

Field operator+(const Field &f, const Move &m)
{
    return Field(f.getX()+m.getX(), f.getY()+m.getY());
}
