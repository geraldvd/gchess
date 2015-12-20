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

string Piece::getTypeString() const
{
    switch(this->type) {
    case KING:
        return "King";
        break;
    case QUEEN:
        return "Queen";
        break;
    case ROOK:
        return "Rook";
        break;
    case BISHOP:
        return "Bishop";
        break;
    case KNIGHT:
        return "Knight";
        break;
    case PAWN:
        return "Pawn";
        break;
    default:
        throw domain_error("Piece type not recognized.");
        break;
    }
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
