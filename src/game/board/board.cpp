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
#include "player.h"

// Specify namespaces
using namespace std;

Board::Board() :
    board_status(BS_NORMAL)
{
    // Setup tiles
    unsigned int i{0};
    while(i < NUM_TILES) {
        this->tiles.push_back(i++);
    }

    // Initialize board
    this->initBoard(0);

    // Setup players - NOTE: must be done after tile initialization
    this->whitePlayer = Player(WHITE, this);
    this->blackPlayer = Player(BLACK, this);
}

void Board::initBoard(const int &board_layout)
{
    switch(board_layout) {
    case 1:
        this->promotionTest();
        break;
    case 2:
        this->castlingTest();
        break;
    default:
        this->standardBoard();
        break;
    }
}

void Board::standardBoard()
{
    // Pawns
    for(int i=8; i<16; i++) {
        this->addPiece(i, PAWN, WHITE);
        this->addPiece(40+i, PAWN, BLACK);
    }

    // White pieces
    this->addPiece(4, KING, WHITE);
    this->addPiece(3, QUEEN, WHITE);
    this->addPiece(0, ROOK, WHITE);
    this->addPiece(7, ROOK, WHITE);
    this->addPiece(2, BISHOP, WHITE);
    this->addPiece(5, BISHOP, WHITE);
    this->addPiece(1, KNIGHT, WHITE);
    this->addPiece(6, KNIGHT, WHITE);

    // Black pieces
    this->addPiece(60, KING, BLACK);
    this->addPiece(59, QUEEN, BLACK);
    this->addPiece(56, ROOK, BLACK);
    this->addPiece(63, ROOK, BLACK);
    this->addPiece(58, BISHOP, BLACK);
    this->addPiece(61, BISHOP, BLACK);
    this->addPiece(57, KNIGHT, BLACK);
    this->addPiece(62, KNIGHT, BLACK);

    // Set active player and calculate possible moves
    this->activePlayer = WHITE;
}

void Board::promotionTest()
{
    // Kings
    this->addPiece(4, KING, WHITE);
    this->addPiece(60, KING, BLACK);

    // Promotion pawn
    this->addPiece(2, 6, PAWN, WHITE);
    this->addPiece(6, 1, PAWN, BLACK);

    // Extra piece (for promotion via capturing)
    this->addPiece(1, 7, KNIGHT, BLACK);

    // Set active player and calculate possible moves
    this->activePlayer = WHITE;
}

void Board::castlingTest()
{
    // Kings
    this->addPiece(4, KING, WHITE);
    this->addPiece(60, KING, BLACK);

    // Rooks
    this->addPiece(0, ROOK, WHITE);
    this->addPiece(7, ROOK, WHITE);
    this->addPiece(56, ROOK, BLACK);
    this->addPiece(63, ROOK, BLACK);

    // Attack one of the fields
    this->addPiece(6, 1, BISHOP, BLACK);

    // Set active player and calculate possible moves
    this->activePlayer = WHITE;
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
    for(unsigned int i=0; i<NUM_TILES; i++) {
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
    if(i>=0 && i<NUM_TILES) {
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

void Board::addPiece(const unsigned int &x, const unsigned int &y, const PieceType &type, const PieceColor &color)
{
    this->addPiece(x + 8*y, type, color);
}

void Board::removePiece(const unsigned int &position)
{
    this->getTile(position)->clearPiece();
}
