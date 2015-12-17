#include "game.h"

// Include standard libraries
#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

Game::Game(const bool &normal_game, const PieceColor & active_player) :
    whiteKing(NULL),
    blackKing(NULL),
    activePlayer(active_player),
    currentPlayerCheck(false)
{
    if(normal_game) {
        this->init();
    }
}

Game::~Game()
{
    // Release memory
    this->resetBoard();
}

void Game::init()
{
    // Clean board
    this->resetBoard();

    // Pawns
    for(int i=0; i<8; i++) {
        this->addPiece(PAWN, Field(i, 1), WHITE);
        this->addPiece(PAWN, Field(i, 6), BLACK);
    }

    // White pieces
    this->addPiece(KING, Field("E1"), WHITE);
    this->addPiece(QUEEN, Field("D1"), WHITE);
    this->addPiece(ROOK, Field("A1"), WHITE);
    this->addPiece(ROOK, Field("H1"), WHITE);
    this->addPiece(BISHOP, Field("C1"), WHITE);
    this->addPiece(BISHOP, Field("F1"), WHITE);
    this->addPiece(KNIGHT, Field("B1"), WHITE);
    this->addPiece(KNIGHT, Field("G1"), WHITE);

    // Black pieces
    this->addPiece(KING, Field("E8"), BLACK);
    this->addPiece(QUEEN, Field("D8"), BLACK);
    this->addPiece(ROOK, Field("A8"), BLACK);
    this->addPiece(ROOK, Field("H8"), BLACK);
    this->addPiece(BISHOP, Field("C8"), BLACK);
    this->addPiece(BISHOP, Field("F8"), BLACK);
    this->addPiece(KNIGHT, Field("B8"), BLACK);
    this->addPiece(KNIGHT, Field("G8"), BLACK);

    // Set active player
    this->activePlayer = WHITE;

    // Initialize all possible moves
    this->updateAllMoves();
}

void Game::initTest()
{
    // Clean board
    this->resetBoard();

    // Pawns
    this->addPiece(PAWN, Field(2, 6), WHITE);
    this->addPiece(PAWN, Field(1, 1), BLACK);

    // White pieces
    this->addPiece(KING, Field("E1"), WHITE);
    this->addPiece(QUEEN, Field("D1"), WHITE);
    this->addPiece(ROOK, Field("A1"), WHITE);
    this->addPiece(ROOK, Field("H1"), WHITE);
    this->addPiece(BISHOP, Field("C1"), WHITE);
    this->addPiece(BISHOP, Field("F1"), WHITE);
    this->addPiece(KNIGHT, Field("G1"), WHITE);

    // Black pieces
    this->addPiece(KING, Field("E8"), BLACK);
    this->addPiece(QUEEN, Field("D8"), BLACK);
    this->addPiece(ROOK, Field("A8"), BLACK);
    this->addPiece(ROOK, Field("H8"), BLACK);

    // Set active player
    this->activePlayer = WHITE;

    // Initialize all possible moves
    this->updateAllMoves();
}

void Game::updateAllMoves()
{
    // Check whether king is check
    if(this->activePlayer == WHITE)
        this->currentPlayerCheck = this->whiteKing->checkStatus(this->pieces);
    else
        this->currentPlayerCheck = this->blackKing->checkStatus(this->pieces);

    // Loop through each piece
    for(auto &p : this->pieces) {
        p.second->getMoves(this->pieces, this->currentPlayerCheck);
    }
}

bool Game::move(Piece *p, const Field &m)
{
    if(p->move(m, this->pieces, this->isCurrentPlayerCheck())) {
        // Calculate all new moves
        this->updateAllMoves();
        // Switch player
        if(this->activePlayer == WHITE) {
            this->activePlayer = BLACK;
        } else {
            this->activePlayer = WHITE;
        }
        return true;
    } else {
        return false;
    }
}

void Game::resetBoard()
{
    // Release memory!
    for(auto &p : this->pieces) {
        delete p.second;
    }

    // Reinitialize pieces vector
    this->pieces.clear();
}

void Game::addPiece(const PieceType &t, const Field &f, const PieceColor &c, const bool &has_moved, const bool &just_moved_double)
{
    switch(t) {
    case KING:
        if(c == WHITE) {
            this->whiteKing = new King(f, c, has_moved);
            this->pieces[f] = this->whiteKing;
        } else {
            this->blackKing = new King(f, c, has_moved);
            this->pieces[f] = this->blackKing;
        }
        break;
    case QUEEN:
        this->pieces[f] = new Queen(f, c, has_moved);
        break;
    case ROOK:
        this->pieces[f] = new Rook(f, c, has_moved);
        break;
    case BISHOP:
        this->pieces[f] = new Bishop(f, c, has_moved);
        break;
    case KNIGHT:
        this->pieces[f] = new Knight(f, c, has_moved);
        break;
    case PAWN:
        this->pieces[f] = new Pawn(f, c, has_moved, just_moved_double);
        break;
    default:
        throw invalid_argument("Piecetype not known");
        break;
    }
}

PieceColor Game::getActivePlayer() const
{
    return this->activePlayer;
}

Piece* Game::getPiece(const Field &f) const
{
    if(this->pieces.find(f) != this->pieces.end()) {
        return this->pieces.at(f);
    } else {
        return NULL;
    }
}

bool Game::isCurrentPlayerCheck() const
{
    return this->currentPlayerCheck;
}

string Game::getActivePlayerString() const
{
    if(this->activePlayer == WHITE)
        return "White";
    else
        return "Black";
}

