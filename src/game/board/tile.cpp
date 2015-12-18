#include "tile.h"


Tile::Tile(const unsigned int &k) :
    field(k%8, (k-k%8)/8),
    piece(NULL)
{
}

Tile::~Tile()
{
        this->clearPiece();
}

Field Tile::getField() const
{
    return this->field;
}

bool Tile::isOccupied() const
{
    if(this->piece == NULL) {
        return false;
    }

    return true;
}

void Tile::setField(const unsigned int &k)
{
    this->field.setX(k%8);
    this->field.setY((k-k%8)/8);
}

void Tile::setPiece(Piece *p)
{
    this->clearPiece();
    this->piece = p;
}

void Tile::clearPiece()
{
    if(this->piece != NULL) {
        // TODO who clears memory?
        delete this->piece;
        this->piece = NULL;
    }
}
