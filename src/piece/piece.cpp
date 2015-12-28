// Include project files
#include "piece.h"
#include "../board/tile.h"

// Specify namespaces
using namespace std;

Piece::Piece(const PieceType &type, const PieceColor & c, const bool &hasMoved, Tile *tile) :
    tile(tile),
    type(type),
    color(c),
    moved(hasMoved)
{
}

Piece::~Piece()
{

}

Tile *Piece::getTile() const
{
    return this->tile;
}

PieceType Piece::getType() const
{
    return this->type;
}

string Piece::getTypeString(const bool &shortNotation) const
{
    switch(this->type) {
    case KING:
        return shortNotation ? (this->color==WHITE ? "K" : "k") : "King";
        break;
    case QUEEN:
        return shortNotation ? (this->color==WHITE ? "Q" : "q") : "Queen";
        break;
    case ROOK:
        return shortNotation ? (this->color==WHITE ? "R" : "r") : "Rook";
        break;
    case BISHOP:
        return shortNotation ? (this->color==WHITE ? "B" : "b") : "Bishop";
        break;
    case KNIGHT:
        return shortNotation ? (this->color==WHITE ? "N" : "n") : "Knight";
        break;
    case PAWN:
        return shortNotation ? (this->color==WHITE ? "P" : "p") : "Pawn";
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

void Piece::setTile(Tile *tile)
{
    this->tile = tile;
}

bool Piece::hasMoved() const
{
    return this->moved;
}

void Piece::setMoved(const bool &hasMoved)
{
    this->moved = hasMoved;
}
