#include "knight.h"

using namespace std;

Knight::Knight(int x, int y, int c) :
    Piece(x, y, c)
{
    this->type = "Knight";
}

void Knight::populateMoves()
{
    // List all move pairs
    vector<pair<int,int> > moves;
    moves.push_back(pair<int,int>(2,1));
    moves.push_back(pair<int,int>(2,-1));
    moves.push_back(pair<int,int>(-2,1));
    moves.push_back(pair<int,int>(-2,-1));
    moves.push_back(pair<int,int>(1,2));
    moves.push_back(pair<int,int>(1,-2));
    moves.push_back(pair<int,int>(-1,2));
    moves.push_back(pair<int,int>(-1,-2));

    // Check whether moves are still on board
    this->setMoves(this->movesOnBoard(moves));
}

