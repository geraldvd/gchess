#include "game.h"

#include <iostream>
#include <algorithm>

using namespace std;

Game::Game(const Color & activePlayer) :
    activePlayer(activePlayer)
{

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
        this->addPawn(i, 1, WHITE);
        this->addPawn(i, 6, BLACK);
    }

    // White pieces
    this->addKing(4, 0, WHITE);
    this->addQueen(3, 0, WHITE);
    this->addRook(0, 0, WHITE);
    this->addRook(7, 0, WHITE);
    this->addKnight(1, 0, WHITE);
    this->addKnight(6, 0, WHITE);
    this->addBishop(2, 0, WHITE);
    this->addBishop(5, 0, WHITE);

    // Black pieces
    this->addKing(4, 7, BLACK);
    this->addQueen(3, 7, BLACK);
    this->addRook(0, 7, BLACK);
    this->addRook(7, 7, BLACK);
    this->addKnight(1, 7, BLACK);
    this->addKnight(6, 7, BLACK);
    this->addBishop(2, 7, BLACK);
    this->addBishop(5, 7, BLACK);

    // Initialize all possible moves
    this->updateAllMoves();
}

void Game::updateAllMoves()
{
    for(auto &p : this->pieces) {
        p->findMoves(this->pieces);
    }
}

void Game::resetBoard()
{
    // Release memory!
    for(Piece* p : this->pieces) {
        delete p;
    }

    // Reinitialize pieces vector
    this->pieces = vector<Piece*>();
}

void Game::addKing(const int & x, const int & y, const Color & c, const bool & hasMoved)
{
    Piece* p = new King(x, y, c, hasMoved);
    this->pieces.push_back(p);
}

void Game::addQueen(const int & x, const int & y, const Color & c, const bool & hasMoved)
{
    Piece* p = new Queen(x, y, c, hasMoved);
    this->pieces.push_back(p);
}

void Game::addRook(const int & x, const int & y, const Color & c, const bool & hasMoved)
{
    Piece* p = new Rook(x, y, c, hasMoved);
    this->pieces.push_back(p);
}

void Game::addKnight(const int & x, const int & y, const Color & c, const bool & hasMoved)
{
    Piece* p = new Knight(x, y, c, hasMoved);
    this->pieces.push_back(p);
}

void Game::addBishop(const int & x, const int & y, const Color & c, const bool & hasMoved)
{
    Piece* p = new Bishop(x, y, c, hasMoved);
    this->pieces.push_back(p);
}

void Game::addPawn(const int & x, const int & y, const Color & c, const bool & hasMoved, const bool & justMovedDouble)
{
    Piece* p = new Pawn(x, y, c, hasMoved, justMovedDouble);
    this->pieces.push_back(p);
}

string Game::getActivePlayer() const
{
    if(this->activePlayer == WHITE)
        return "White";
    else
        return "Black";
}

vector<Piece *> Game::getPieces() const
{
    return this->pieces;
}

