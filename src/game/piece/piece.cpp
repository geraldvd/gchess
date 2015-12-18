#include "piece.h"

#include <sstream>
#include <algorithm>

using namespace std;

Piece::Piece(const PieceColor & c, const bool &has_moved) :
    color(c),
    has_moved(has_moved)
{
}

Piece::~Piece()
{

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
