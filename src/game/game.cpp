#include "game.h"

#include <iostream>

using namespace std;

Game::Game()
{

}

void Game::init()
{
    // Pawns
    for(int i=0; i<8; i++) {
        this->addWhitePiece(new Pawn(i, 1, 1));
        this->addBlackPiece(new Pawn(i, 1, -1));
    }

    // White pieces
    this->addWhitePiece(new King(4, 0, 1));
    this->addWhitePiece(new Queen(3, 0, 1));
    this->addWhitePiece(new Rook(0, 0, 1));
    this->addWhitePiece(new Rook(7, 0, 1));
    this->addWhitePiece(new Knight(1, 0, 1));
    this->addWhitePiece(new Knight(6, 0, 1));
    this->addWhitePiece(new Bishop(2, 0, 1));
    this->addWhitePiece(new Bishop(5, 0, 1));

    // Black pieces
    this->addBlackPiece(new King(4, 0, -1));
    this->addBlackPiece(new Queen(3, 0, -1));
    this->addBlackPiece(new Rook(0, 0, -1));
    this->addBlackPiece(new Rook(7, 0, -1));
    this->addBlackPiece(new Knight(1, 0, -1));
    this->addBlackPiece(new Knight(6, 0, -1));
    this->addBlackPiece(new Bishop(2, 0, -1));
    this->addBlackPiece(new Bishop(5, 0, -1));
}

bool Game::isValidMove(Piece *p, std::pair<int, int> m)
{
    bool valid{false};

    // Check moves without checking environment
    for(auto &i : p->getMoves()) {
        if(m==i) {
            valid = true;
        }
    }

    // Return if false
    if(! valid) return valid;

    // Check own pieces
    vector<Piece*> myPieces;
    if(p->getColor() > 0)
        myPieces = this->getWhitePieces();
    else
        myPieces = this->getBlackPieces();

    for(auto &mp : myPieces) {
        // Cannot be on top of other piece
        if(m==mp->getPosition()) {
            valid = false;
            return valid;
        }

        // Only knigh can jump over pieces
        if(mp->getType() != "Knight") {


        } else {
        }
    }

    // Check opponent pieces

    // Check check status king

    // Return result
    return valid;
}

vector<pair<int, int> > Game::getValidMoves(Piece * p) const
{
    // TODO finish this function to get all possible moves of a piece!
    auto moves = p->getMoves();
    vector<pair<int,int> > newMoves;

    // Obtain own and opponent pieces
    vector<Piece*> myPieces;
    vector<Piece*> opponentPieces;
    if(p->getColor() > 0) {
        myPieces = this->getWhitePieces();
        opponentPieces = this->getBlackPieces();
    } else {
        myPieces = this->getBlackPieces();
        opponentPieces = this->getWhitePieces();
    }

    // Check own pieces
    vector<Piece*> obstructingPieces;
    bool valid;
    for(auto &m : moves) {
        // Assume valid move
        valid = true;

        // Find moves on top of other pieces
        for(auto &mp : myPieces) {
            if(m==mp->getPosition()) {
                obstructingPieces.push_back(mp);
                valid = false;
            }
        }

        if(valid)
            newMoves.push_back(m);
    }
    // New moves become old moves
    moves = newMoves;
    newMoves = vector<pair<int,int> >();

    for(auto &m : moves) {
        for(Piece* mp : obstructingPieces) {
            // Check whether moves are behind piece!
            if(mp->getType() == "Knight" || mp->getType() == "King") {
                // Knight jumps over pieces, king can only move 1 step!
                break;
            } else if(mp->getType() == "Queen") {
                if(mp->getPosition().first - p->getPosition().first && mp->getPosition().second - p->getPosition().second) {
                    // Obstructing piece on diagonal
                    if(m.first - mp->getPosition().first != m.second - mp->getPosition().second) {
                        newMoves.push_back(m);
                        // TODO: mistake, diagonal might be the other side than obstructing piece!
                        break;
                    }
                } else if(mp->getPosition().first - p->getPosition().first) {
                    // Obstructing piece in x
                    // TODO start here
                }

            } else if(mp->getType() == "Rook") {

            } else if(mp->getType() == "Bishop") {

            } else if(mp->getType() == "Pawn") {

            }
        }
    }

    // Return remaining moves
    return newMoves;
}

void Game::updateMoves(Piece *p)
{
    vector<pair<int,int> > newMoves;

    for(auto &m : p->getMoves()) {
        if(this->isValidMove(p, m)) {
            newMoves.push_back(m);
        }
    }

    p->setMoves(newMoves);
}

void Game::updateAllMoves()
{
    for(auto &p : this->getWhitePieces()) {
        this->updateMoves(p);
    }

    for(auto &p : this->getBlackPieces()) {
        this->updateMoves(p);
    }
}

void Game::addWhitePiece(Piece *p)
{
    this->white.push_back(p);

    // Initialize possible moves
    p->findTheoreticalMoves();
}

void Game::addBlackPiece(Piece *p)
{
    this->black.push_back(p);

    // Initialize possible moves
    p->findTheoreticalMoves();
}

vector<Piece *> Game::getBlackPieces() const
{
    return this->black;
}

vector<Piece *> Game::getWhitePieces() const
{
    return this->white;
}

