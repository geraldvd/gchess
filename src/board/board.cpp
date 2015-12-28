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
#include "../player/player.h"

// Specify namespaces
using namespace std;

Board::Board(const PieceColor &activePlayer, const BoardStatus &bs) :
    tiles(NUM_TILES),
    board_status(bs),
    activePlayer(activePlayer)
{
    // Setup tiles
    for(unsigned int i=0; i<NUM_TILES_X; i++) {
        for(unsigned int j=0; j<NUM_TILES_Y; j++) {
            this->tiles.at(Field(i, j).getPosition()) = Tile(i, j);
        }
    }
}

Tile *Board::getTile(const unsigned int &x, const unsigned int &y)
{
    if(find(this->tiles.begin(), this->tiles.end(), Field(x, y).getPosition()) != this->tiles.end()) {
        return &this->tiles.at(Field(x, y).getPosition());
    } else {
        throw invalid_argument("x or y falls outside board!");
    }
}

Tile *Board::getTile(const Field &f)
{
    return this->getTile(f.getX(), f.getY());
}

std::vector<Tile*> Board::getTiles()
{
    vector<Tile*> tiles;

    for(auto tile : this->tiles) {
        tiles.push_back(&tile);
    }
    return tiles;
}

std::vector<Piece_ptr> Board::getPieces()
{
    vector<Piece_ptr> pieces;
    for(auto t : this->getTiles()) {
        if(t->isOccupied()) {
            pieces.push_back(t->getPiece());
        }
    }
    return pieces;
}

bool Board::isOnBoard(const int &x, const int &y) const
{
    if(x>=0 && x<8 && y>=0 && y<8) {
        return true;
    }
    return false;
}

void Board::addPiece(const unsigned int &x, const unsigned int &y, const PieceType &type, const PieceColor &color)
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

    this->pieces.push_back(p);
    p->setTile(this->getTile(x, y));
    this->getTile(x, y)->setPiece(p);
}


BoardStatus Board::getBoardStatus() const
{
    return this->board_status;
}

string Board::getBoardStatusString() const
{
    string status;
    switch(this->board_status) {
    case BS_NORMAL:
        status = "Normal";
        break;
    case BS_UNKNOWN:
        status = "Unknonw";
        break;
    case BS_CHECKBLACK:
        status = "Check black";
        break;
    case BS_CHECKWHITE:
        status = "Check white";
        break;
    case BS_CHECKMATEBLACK:
        status = "Checkmate black";
        break;
    case BS_CHECKMATEWHITE:
        status = "Checkmate white";
        break;
    case BS_STALEMATE:
        status = "Stalemate";
        break;
    }

    return status;
}

void Board::setBoardStatus(const BoardStatus &bs)
{
    this->board_status = bs;
}

PieceColor Board::getActiveColor()
{
    return this->activePlayer;
}

string Board::getActiveColorString() const
{
    if(this->activePlayer == WHITE) {
        return "white";
    } else {
        return "black";
    }
}

void Board::setActiveColor(const PieceColor &color)
{
    this->activePlayer = color;
}

void Board::switchPlayer()
{
    if(this->activePlayer == WHITE) {
        this->activePlayer = BLACK;
    } else {
        this->activePlayer = WHITE;
    }
}
