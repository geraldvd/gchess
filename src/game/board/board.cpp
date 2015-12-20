// Include standard libraries
#include <stdexcept>
#include <memory>
#include <algorithm>

// Include project files
#include "board.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"

// Specify namespaces
using namespace std;

Board::Board() :
    board_status(BS_NORMAL)
{
    unsigned int i{0};
    while(i < Board::NUM_TILES) {
        this->tiles.push_back(i++);
    }
}

Tile *Board::getTile(const unsigned int &i)
{
    return &this->tiles.at(i);
}

Tile *Board::getTile(const unsigned int &x, const unsigned int &y)
{
    unsigned int i = x + 8*y;
    if(find(this->tiles.begin(), this->tiles.end(), i) != this->tiles.end()) {
        return &this->tiles.at(i);
    }
    return NULL;
}

std::vector<Tile*> Board::getTiles()
{
    vector<Tile*> tiles;
    for(unsigned int i=0; i<Board::NUM_TILES; i++) {
        tiles.push_back(this->getTile(i));
    }
    return tiles;
}

std::vector<Piece_ptr> Board::getPieces()
{
    vector<Piece_ptr> pieces;
    for(Tile* t : this->getTiles()) {
        if(t->isOccupied()) {
            pieces.push_back(t->getPiece());
        }
    }
    return pieces;
}

bool Board::isOnBoard(const int &i) const
{
    if(i>=0 && i<int(Board::NUM_TILES)) {
        return true;
    }
    return false;
}

bool Board::isOnBoard(const int &x, const int &y) const
{
    if(x>=0 && x<8 && y>=0 && y<8) {
        return true;
    }
    return false;
}

void Board::addPiece(const unsigned int &position, const PieceType &type, const PieceColor &color)
{
    // Create piece
    Piece_ptr p;
    switch(type) {
    case KING:
        p.reset(new King(color));
        break;
    case QUEEN:
        p.reset(new Queen(color));
        break;
    case ROOK:
        p.reset(new Rook(color));
        break;
    case BISHOP:
        p.reset(new Bishop(color));
        break;
    case KNIGHT:
        p.reset(new Knight(color));
        break;
    case PAWN:
        p.reset(new Pawn(color));
        break;
    default:
        throw invalid_argument("Type not recognized.");
    }

    p->setTile(this->getTile(position));
    this->getTile(position)->setPiece(p);
}

void Board::removePiece(const unsigned int &position)
{
    this->getTile(position)->clearPiece();
}
