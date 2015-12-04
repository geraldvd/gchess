#include "king.h"

using namespace std;

King::King(int x, int y, int c) :
    Piece(x, y, c)
{
    this->type = "King";
}

std::vector<Field> King::findTheoreticalMoves()
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
    return this->movesOnBoard(moves);
}

