// Include standard libraries
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <iostream>

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

Board::Board(const PieceColor &activePlayer, const BoardStatus &bs) :
    tiles(NUM_TILES),
    whiteKing(NULL),
    blackKing(NULL),
    board_status(bs)
{
    this->setActivePlayer(WHITE);

    // Setup tiles
    for(unsigned int i=0; i<NUM_TILES_X; i++) {
        for(unsigned int j=0; j<NUM_TILES_Y; j++) {
            this->tiles.at(Field(i, j).getPosition()) = Tile(i, j);
        }
    }
}

Board::Board(const string & board) :
    Board(WHITE, BS_NORMAL)
{
    // Active player
    if(board.at(0) == 'w') {
        this->setActivePlayer(WHITE);
    } else {
        this->setActivePlayer(BLACK);
    }

    // Board status
    this->setBoardStatus(BoardStatus(static_cast<int>(board.at(1)) - '0'));

    // Pieces
    for(unsigned i=2; i<board.length(); i+=6) {
        Field position(board.substr(i, 2));
        PieceColor color = board.at(i+2)=='w' ? WHITE : BLACK;
        PieceType type;
        switch(board.at(i+3)) {
        case 'K':
            type = KING;
            break;
        case 'Q':
            type = QUEEN;
            break;
        case 'R':
            type = ROOK;
            break;
        case 'B':
            type = BISHOP;
            break;
        case 'N':
            type = KNIGHT;
            break;
        case 'P':
            type = PAWN;
            break;
        }
        bool hasMoved = static_cast<int>(board.at(i+4)) - '0';
        bool justMovedDouble = static_cast<int>(board.at(i+5)) - '0';

        this->addPiece(position.getX(), position.getY(), type, color, hasMoved, justMovedDouble);
    }
}

string Board::get() const
{
    // Note: bitshift right => fill with 0; bitshift left => fill with 1
    string board;

    // Other board info
    board += this->activePlayer==WHITE ? "w" : "b";
    board += to_string(this->board_status);

    // Pieces
    for(auto &p : this->pieces) {
        board += p->toString();
    }

    return board;
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

    for(auto &tile : this->tiles) {
        tiles.push_back(&tile);
    }
    return tiles;
}

std::vector<Piece_ptr> Board::getPieces()
{
    vector<Piece_ptr> pieces;
    for(auto &t : this->getTiles()) {
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

void Board::addPiece(const unsigned int &x, const unsigned int &y, const PieceType &type, const PieceColor &color,
                     const bool &moved, const bool &justMovedDouble)
{
    // Create piece
    Piece_ptr p;
    switch(type) {
    case KING:
        if(color == WHITE) {
            if(this->whiteKing != NULL) {
                throw domain_error("Only one white king is allowed on the board.");
            }

            this->whiteKing.reset(new King(color));
            p = this->whiteKing;
        } else {
            if(this->blackKing != NULL) {
                throw domain_error("Only one black king is allowed on the board.");
            }

            this->blackKing.reset(new King(color));
            p = this->blackKing;
        }
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

    // Set properties
    p->setMoved(moved);
    p->setJustMovedDouble(justMovedDouble);

    this->pieces.push_back(p);
    p->setTile(this->getTile(x, y));
    this->getTile(x, y)->setPiece(p);
}

std::shared_ptr<King> Board::getActiveKing()
{
    return this->activePlayer==WHITE ? this->whiteKing : this->blackKing;
}

std::shared_ptr<King> Board::getInActiveKing()
{
    return this->activePlayer==WHITE ? this->blackKing : this->whiteKing;
}

bool Board::activeKingCheck() const
{
    if((this->activePlayer == WHITE && (this->board_status == BS_CHECKWHITE || this->board_status == BS_CHECKMATEWHITE)) ||
        (this->activePlayer == BLACK && (this->board_status == BS_CHECKBLACK || this->board_status == BS_CHECKMATEBLACK))) {
        return true;
    }
    return false;
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

PieceColor Board::getActivePlayer() const
{
    return this->activePlayer;
}

PieceColor Board::getInActivePlayer() const
{
    if(this->activePlayer == WHITE) {
        return BLACK;
    } else {
        return WHITE;
    }
}

string Board::getActivePlayerString() const
{
    return this->activePlayer==WHITE ? "white" : "black";
}

void Board::setActivePlayer(const PieceColor & color)
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

void Board::calculatePotentialMoves()
{
    vector<Move> moves;

    for(auto &t : this->getTiles()) {
        if(t->isOccupied() /*&& t->getPiece()->getColor() == this->color*/) {
            vector<Move> pieceMoves = t->getPiece()->calculateMoves(this);
            moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
        }
    }

    this->potentialMoves = moves;
}

Board Board::move(Move & m)
{
    if(this->boardsAfterMoves.find(m) == boardsAfterMoves.end()) {
        return *this;
    } else {
        //return m.execute(this);
        return Board(this->boardsAfterMoves[m]);
    }
}

void Board::updateMoves()
{
    this->calculatePotentialMoves();
    map<Move, string> boardsAfterMoves;

    for(auto &m : this->potentialMoves) {
        if(m.getMovingPiece()->getColor() != this->activePlayer) {
            // Opponent's move
            continue;
        }
        // Virtual move execution
        Board boardAfterMove = m.execute(this);

        // Check castling
        if(m.getMoveType() == MT_CASTLING) {
            vector<int> xCastlingUnderAttack{m.getMovingPiece()->getTile()->getX(),
                                             m.getDestination().getX(),
                                             (m.getMovingPiece()->getTile()->getX() + m.getDestination().getX())/2};
            bool castlingValid{true};
            for(auto &i : xCastlingUnderAttack) {
                // Check whether fields are in CHECK on old board
                if(this->getTile(i, m.getDestination().getY())->attackingPieces(this, this->getInActivePlayer()).size() != 0) {
                    // One of the fields passed by king to castle is under attack
                    castlingValid = false;
                }
            }
            if(! castlingValid) {
                continue;
            }
        }

        // CHECK status
        if(boardAfterMove.getInActiveKing()->getTile()->attackingPieces(&boardAfterMove, boardAfterMove.getActivePlayer()).size() != 0) {
            // Not allowed, moving into check
            continue;
        }

        // Add move to  allowed moves
        boardsAfterMoves[m] = boardAfterMove.get();
    }


    // Checkmate or stalemate?
    if(boardsAfterMoves.size() == 0) {
        if(this->getBoardStatus() == BS_CHECKWHITE && this->getActivePlayer() == WHITE) {
                this->setBoardStatus(BS_CHECKMATEWHITE);
        } else if(this->getBoardStatus() == BS_CHECKBLACK && this->getActivePlayer() == BLACK) {
                this->setBoardStatus(BS_CHECKMATEBLACK);
        } else {
            this->setBoardStatus(BS_STALEMATE);
        }
    }

    this->boardsAfterMoves = boardsAfterMoves;
}

std::vector<Move> Board::getMoves() const
{
    vector<Move> moves;

    for(auto &m : this->boardsAfterMoves) {
        moves.push_back(m.first);
    }

    return moves;
}

std::map<Move, string> Board::getBoardsAfterMoves() const
{
    return this->boardsAfterMoves;
}

std::vector<Move> Board::getPotentialMoves() const
{
    return this->potentialMoves;
}

int Board::computeBoardValue()
{

    // Checkmate
    if(this->board_status == BS_CHECKMATEWHITE) {
        return 100;
    } else if(this->board_status == BS_CHECKMATEBLACK) {
        return -100;
    }

    // Check value if not checkmate
    int value{0};

    // Compute piece values
    for(auto &p : this->getPieces()) {
        value += p->getColor()==WHITE ? p->getValue() : -p->getValue();
    }

    // Check status
    if(this->board_status == BS_CHECKWHITE || this->board_status == BS_CHECKBLACK) {
        // TODO
    }

    // TDOO extend this!
    return value;
}
