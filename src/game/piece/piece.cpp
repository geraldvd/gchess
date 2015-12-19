#include "piece.h"

#include <sstream>
#include <algorithm>

using namespace std;

Piece::Piece(const unsigned int &position, const PieceColor & c, const bool &has_moved) :
    position(position),
    color(c),
    has_moved(has_moved)
{
}

Piece::~Piece()
{

}

unsigned int Piece::getPosition() const
{
    return this->position;
}

PieceType Piece::getType() const
{
    return this->type;
}

PieceColor Piece::getColor() const
{
    return this->color;
}

string Piece::getColorString() const
{
    if(this->color == WHITE) {
        return string("white");
    } else {
        return string("black");
    }
}
