// Include standard library
#include <stdexcept>

// Include project files
#include "move.h"
#include "board.h"

// Specify namespaces
using namespace std;

Move::Move() :
    Move(0, MT_NONE)
{
}

Move::Move(const int &x, const int &y, const MoveType &mt) :
    Field(x, y),
    moveType(mt),
    moveValid(true),
    castlingRookPosition(0)
{
}

Move::Move(const int &m, const MoveType &mt) :
    Field(m),
    moveType(mt),
    castlingRookPosition(0)
{
}

MoveType Move::getMoveType() const
{
    return this->moveType;
}

Field Move::getCastlingRookPosition() const
{
    return this->castlingRookPosition;
}

void Move::setMoveType(const MoveType &mt)
{
    this->moveType = mt;
}

void Move::setValidity(const bool &valid)
{
    this->moveValid = valid;
}

bool Move::isValid() const
{
    return this->moveValid;
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

Piece_ptr Move::getMovingPiece() const
{
    return this->movingPiece;
}
