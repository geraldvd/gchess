// Include standard libraries
#include <stdexcept>

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

std::vector<Tile*> Board::getTiles()
{
    vector<Tile*> tiles;
    for(unsigned int i=0; i<Board::NUM_TILES; i++) {
        tiles.push_back(this->getTile(i));
    }
    return tiles;
}

std::vector<Piece *> Board::getPieces()
{
    vector<Piece*> pieces;
    for(Tile* t : this->getTiles()) {
        if(t->isOccupied()) {
            pieces.push_back(t->getPiece());
        }
    }
    return pieces;
}

bool Board::isOnBoard(const unsigned int &i) const
{
    if(i>=0 && i<Board::NUM_TILES) {
        return true;
    }
    return false;
}

void Board::addPiece(const unsigned int &position, const PieceType &type, const PieceColor &color)
{
    // Create piece
    Piece* p{NULL};
    switch(type) {
    case KING:
        p = new King(position, color);
        break;
    case QUEEN:
        p = new Queen(position, color);
        break;
    case ROOK:
        p = new Rook(position, color);
        break;
    case BISHOP:
        p = new Bishop(position, color);
        break;
    case KNIGHT:
        p = new Knight(position, color);
        break;
    case PAWN:
        p = new Pawn(position, color);
        break;
    default:
        throw invalid_argument("Type not recognized.");
    }


    this->getTile(position)->setPiece(p);
}

void Board::removePiece(const unsigned int &position)
{
    this->getTile(position)->clearPiece();
}
