// Include standard libraries
#include <stdexcept>

// Include project files
#include "tile.h"
#include "board/board.h"

// Specify namespaces
using namespace std;


Tile::Tile(const unsigned int &p) :
    Field(p)
{
}

Tile::Tile(const unsigned int &x, const unsigned int &y) :
    Field(x, y)
{
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


void Tile::setPiece(Piece_ptr p)
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

bool Tile::tileUnderAttack(Board *b)
{
    for(auto &p : b->getPieces()) {
        // Check whether field is empty OR has opposing color
        if(/*(this->isOccupied() && this->getPiece()->getColor() != p->getColor()) || */p->getColor() != b->getActivePlayer()->getColor()) {
            for(auto &m : p->calculateMoves(b)) {
                if(m.getPosition() == this->getPosition()) {
                    return true;
                }
            }
        }
    }
    return false;
}
