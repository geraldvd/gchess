#include "bishop.h"

using namespace std;

Bishop::Bishop(int x, int y, int c) :
    Piece(x, y, c)
{
    this->type = "Bishop";
}

void Bishop::populateMoves()
{
    // List all move pairs
    vector<pair<int,int> > moves;
    for(int i=1; i<8; i++) {
        // Diagonal moves
        moves.push_back(pair<int,int>(i,i));
        moves.push_back(pair<int,int>(-i,-i));
        moves.push_back(pair<int,int>(i,-i));
        moves.push_back(pair<int,int>(-i,i));
    }

    // Check whether moves are still on board
    this->setMoves(this->movesOnBoard(moves));
}

