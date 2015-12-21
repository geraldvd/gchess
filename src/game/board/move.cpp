// Include standard library
#include <stdexcept>

// Include project files
#include "move.h"
#include "board.h"

// Specify namespaces
using namespace std;

Move::Move(const int &x, const int &y, const MoveType &mt) :
    Field(x, y),
    move_type(mt),
    castlingRookPosition(0)
{
}

Move::Move(const int &m, const MoveType &mt) :
    Field(m),
    move_type(mt),
    castlingRookPosition(0)
{
}

MoveType Move::getMoveType() const
{
    return this->move_type;
}

unsigned int Move::getCastlingRookPosition() const
{
    return this->castlingRookPosition;
}

void Move::setMoveType(const MoveType &mt)
{
    this->move_type = mt;
}

void Move::setCatlingRookPosition(const unsigned int &position)
{
    this->castlingRookPosition = position;
}

bool Move::execute(Board* b)
{
    // TODO
    return true;
}
