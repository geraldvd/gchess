#include "game.h"

using namespace std;

Game::Game()
{

}

void Game::init()
{
    // Pawns
    for(int i=0; i<8; i++) {
        this->addWhitePiece(new Pawn(i, 1));
        this->addBlackPiece(new Pawn(i, 1));
    }

    // White pieces
    this->addWhitePiece(new King(4, 0));
    this->addWhitePiece(new Queen(5, 0));
    this->addWhitePiece(new Rook(0, 0));
    this->addWhitePiece(new Rook(7, 0));
    this->addWhitePiece(new Knight(1, 0));
    this->addWhitePiece(new Knight(6, 0));
    this->addWhitePiece(new Bishop(2, 0));
    this->addWhitePiece(new Bishop(5, 0));

    // Black pieces
    this->addBlackPiece(new King(4, 0));
    this->addBlackPiece(new Queen(5, 0));
    this->addBlackPiece(new Rook(0, 0));
    this->addBlackPiece(new Rook(7, 0));
    this->addBlackPiece(new Knight(1, 0));
    this->addBlackPiece(new Knight(6, 0));
    this->addBlackPiece(new Bishop(2, 0));
    this->addBlackPiece(new Bishop(5, 0));
}

bool Game::isValidMove(Piece *p, std::pair<int, int> m)
{
    for(auto &i : p->getMoves()) {
        if(m==i) {
            return true;
        }
    }

    // No match found
    return false;
}

void Game::addWhitePiece(Piece *p)
{
    this->white.push_back(p);
}

void Game::addBlackPiece(Piece *p)
{
    this->black.push_back(p);
}

