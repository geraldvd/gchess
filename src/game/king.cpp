#include "king.h"

using namespace std;

King::King(int x, int y) :
    Piece(x, y)
{

}

void King::populateMoves()
{
    // List all move pairs
    vector<pair<int,int> > moves;
    moves.push_back(pair<int,int>(1,0));
    moves.push_back(pair<int,int>(-1,0));
    moves.push_back(pair<int,int>(0,1));
    moves.push_back(pair<int,int>(0,-1));
    moves.push_back(pair<int,int>(1,1));
    moves.push_back(pair<int,int>(-1,-1));
    moves.push_back(pair<int,int>(-1,1));
    moves.push_back(pair<int,int>(1,-1));

    // Check whether moves are still on board
    this->setMoves(this->movesOnBoard(moves));
}

