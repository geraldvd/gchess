#include "pawn.h"

using namespace std;

Pawn::Pawn(int x, int y, int c) :
    Piece(x, y, c)
{
    this->type = "Pawn";
}

void Pawn::findTheoreticalMoves()
{
    // List all move pairs
    vector<pair<int,int> > moves;
    moves.push_back(pair<int,int>(0,1));
    if(this->getPosition().second == 1) {
        // Pawn did not move yet
        moves.push_back(pair<int,int>(0,2));
    }

    // Check whether moves are still on board
    this->setMoves(this->movesOnBoard(moves));
}

