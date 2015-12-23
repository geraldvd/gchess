// Include project files
#include "piece.h"
#include "../board/tile.h"

// Specify namespaces
using namespace std;

Piece::Piece(const PieceType &type, const PieceColor & c, const bool &has_moved, Tile* parent) :
    tile(parent),
    type(type),
    color(c),
    has_moved(has_moved)
{
}

Piece::~Piece()
{

}

Tile *Piece::getTile()
{
    return this->tile;
}

PieceType Piece::getType() const
{
    return this->type;
}

string Piece::getTypeString(const bool &short_notation) const
{
    switch(this->type) {
    case KING:
        return short_notation ? (this->color==WHITE ? "K" : "k") : "King";
        break;
    case QUEEN:
        return short_notation ? (this->color==WHITE ? "Q" : "q") : "Queen";
        break;
    case ROOK:
        return short_notation ? (this->color==WHITE ? "R" : "r") : "Rook";
        break;
    case BISHOP:
        return short_notation ? (this->color==WHITE ? "B" : "b") : "Bishop";
        break;
    case KNIGHT:
        return short_notation ? (this->color==WHITE ? "N" : "n") : "Knight";
        break;
    case PAWN:
        return short_notation ? (this->color==WHITE ? "P" : "p") : "Pawn";
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

bool Piece::hasMoved() const
{
    return this->has_moved;
}

void Piece::setTile(Tile *tile)
{
    this->tile = tile;
}

void Piece::setMoved()
{
    this->has_moved = true;
}
