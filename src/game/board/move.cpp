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

Move::Move(const unsigned int &old_position, const std::pair<unsigned int, unsigned int> &move, const MoveType &mt) :

{

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
    this->x = x;
}

void Move::setY(const int &y)
{
    this->y = y;
}
