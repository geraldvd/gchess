#include "queen.h"

using namespace std;

Queen::Queen(int x, int y) :
    Piece(x, y)
{

}

void Queen::populateMoves()
{
    // List all move pairs
    vector<pair<int,int> > moves;
    for(int i=1; i<8; i++) {
        // Straight moves
        moves.push_back(pair<int,int>(i,0));
        moves.push_back(pair<int,int>(-i,0));
        moves.push_back(pair<int,int>(0,i));
        moves.push_back(pair<int,int>(0,-i));

        // Diagonal moves
        moves.push_back(pair<int,int>(i,i));
        moves.push_back(pair<int,int>(-i,-i));
        moves.push_back(pair<int,int>(i,-i));
        moves.push_back(pair<int,int>(-i,i));
    }

    // Check whether moves are still on board
    this->setMoves(this->movesOnBoard(moves));
}

