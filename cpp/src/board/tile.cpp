// Include standard libraries
#include <stdexcept>

// Include project files
#include "tile.h"
#include "board.h"
#include "../player/player.h"

// Specify namespaces
using namespace std;


Tile::Tile() :
    Tile(0,0)
{
}

Tile::Tile(const unsigned int &x, const unsigned int &y) :
    Field(x, y),
    piece(NULL)
{
}

std::vector<Piece_ptr> Tile::attackingPieces(Board *b, const PieceColor &attackingColor)
{
    // Note: multiple pieces can attack a tile
    vector<Piece_ptr> attackingPieces;

    for(auto &m : /*b->getAllPotentialMoves()*/b->getPotentialMoves()) {
        if(m.getMovingPiece()->getColor() == attackingColor && m.getDestination() == *this) {
            attackingPieces.push_back(m.getMovingPiece());
        }
    }
    return attackingPieces;
}

Piece_ptr Tile::getPiece() const
{
    return this->piece;
}

bool Tile::isOccupied() const
{
    if(this->piece == NULL) {
        return false;
    }

    return true;
}


void Tile::setPiece(const Piece_ptr &p)
{
    this->piece = p;
    p->setTile(this);
}

void Tile::clearPiece()
{
    if(this->piece != NULL) {
        this->piece = NULL;
    }
}
