#include <iostream>
// Include project files
#include "piece.h"
#include "../board/tile.h"
#include "pawn.h"

// Specify namespaces
using namespace std;

Piece::Piece(const PieceType &type, const PieceColor & c, const bool &hasMoved, const bool & justMovedDouble, Tile *tile) :
    tile(tile),
    type(type),
    color(c),
    moved(hasMoved),
    justMovedDouble(justMovedDouble)
{
}

Piece::~Piece()
{

}

string Piece::toString() const
{
    string result = this->tile->getPositionString();
    result += this->color==WHITE ? "w" : "b";
    switch(this->type) {
    case KING:
        result += "K";
        break;
    case QUEEN:
        result += "Q";
        break;
    case ROOK:
        result += "R";
        break;
    case BISHOP:
        result += "B";
        break;
    case KNIGHT:
        result += "N";
        break;
    case PAWN:
        result += "P";
        break;
    }
    result += this->moved ? "1" : "0";
    result += this->justMovedDouble ? "1" : "0";

    return result;
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

bool Piece::getJustMovedDouble() const
{
    return this->justMovedDouble;
}

void Piece::setJustMovedDouble(const bool & d)
{
    this->justMovedDouble = d;
}

unsigned int Piece::getHash() const
{
    unsigned int h = 31;
    h = (h*HASH_A) ^ (this->tile->getHash()*HASH_B);
    h = (h*HASH_A) ^ (this->type*HASH_B);
    h = (h*HASH_A) ^ (this->color*HASH_B);
    h = this->moved ? (h*HASH_A) ^ (this->moved*HASH_B) : h*HASH_A;

    return h % HASH_C;
}
