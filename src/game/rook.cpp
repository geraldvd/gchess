#include "rook.h"

using namespace std;

Rook::Rook(int x, int y, int c) :
    Piece(x, y, c)
{
    this->type = "Rook";
}

void Rook::findTheoreticalMoves()
{
    // List all move pairs
    vector<pair<int,int> > moves;
    for(int i=1; i<8; i++) {
        // Straight moves
        moves.push_back(pair<int,int>(i,0));
        moves.push_back(pair<int,int>(-i,0));
        moves.push_back(pair<int,int>(0,i));
        moves.push_back(pair<int,int>(0,-i));
    }

    // Check whether moves are still on board
    this->setMoves(this->movesOnBoard(moves));
}

