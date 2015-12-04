#include "knight.h"

using namespace std;

Knight::Knight(int x, int y, int c) :
    Piece(x, y, c)
{
    this->type = "Knight";
}

std::vector<Field> Knight::findTheoreticalMoves()
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
    return this->movesOnBoard(moves);
}

