#include "piece.h"

using namespace std;

Piece::Piece(int x, int y) :
    position(x,y)
{

}

std::vector<std::pair<int, int> > Piece::getMoves() const
{
    return this->moves;
}

void Piece::setMoves(const std::vector<std::pair<int, int> > & moves)
{
    this->moves = moves;
}

std::pair<int, int> Piece::getPosition() const
{
    return this->position;
}

void Piece::setPosition(const std::pair<int, int> & p)
{
    this->position = p;
}



vector<pair<int,int> > Piece::movesOnBoard(vector<pair<int, int> > moves)
{
    vector<pair<int,int> > possibleMoves;

    for(auto &m : moves) {
        auto x = this->position.first + m.first;
        auto y = this->position.second + m.second;

        if(x>=0 && x<8 && y>=0 && y<8) {
            possibleMoves.push_back(m);
        }
    }

    return possibleMoves;
}

