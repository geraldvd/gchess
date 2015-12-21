// Include standard library
#include <stdexcept>

// Include project files
#include "move.h"
#include "board.h"

// Specify namespaces
using namespace std;

Move::Move(const int &x, const int &y, const MoveType &mt) :
    move_type(mt),
    castlingRookPosition(0)
{
    this->setX(x);
    this->setY(y);
}

Move::Move(const unsigned int &m, const MoveType &mt) :
    move_type(mt),
    castlingRookPosition(0)
{
    this->set(m);
}

unsigned int Move::get() const
{
    return this->destination;
}

unsigned int Move::getX() const
{
    return this->destination%8;
}

unsigned int Move::getY() const
{
    return (this->destination - this->getX()) / 8;
}

MoveType Move::getMoveType() const
{
    return this->move_type;
}

unsigned int Move::getCastlingRookPosition() const
{
    return this->castlingRookPosition;
}

void Move::set(const unsigned int &m)
{
    if(m>=0 && m<Board::NUM_TILES) {
        this->destination = m;
    } else {
        throw invalid_argument("Move must be between 0 and 63.");
    }
}

void Move::setMoveType(const MoveType &mt)
{
    this->move_type = mt;
}

void Move::setCatlingRookPosition(const unsigned int &position)
{
    this->castlingRookPosition = position;
}

void Move::setX(const unsigned int &x)
{
    if(x>=0 && x<Board::NUM_TILES/8) {
        unsigned int old_x = this->getX();
        this->destination += (x - old_x);
    }
}

void Move::setY(const unsigned int &y)
{
    if(y>=0 && y<Board::NUM_TILES/8) {
        unsigned int old_y = this->getY();
        this->destination += 8*(y - old_y);
    }
}
