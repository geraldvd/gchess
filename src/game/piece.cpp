#include "piece.h"

#include <sstream>

using namespace std;

Piece::Piece(int x, int y, int c) :
    position(x,y),
    color(c)
{

}

std::vector<std::pair<int, int> > Piece::getMoves() const
{
    return this->moves;
}

std::vector<std::pair<int, int> > Piece::getGlobalMoves() const
{
    vector<pair<int,int> > moves = this->getMoves();

    if(this->getColor() < 0) {
        // Black moves must be transformed
        for(auto &m : moves) {
            m.second = 7 - m.second;
        }
    } else {
        // White moves correct by default
    }

    return moves;
}

void Piece::setMoves(const std::vector<std::pair<int, int> > & moves)
{
    this->moves = moves;
}

std::pair<int, int> Piece::getPosition() const
{
    return this->position;
}

std::pair<int, int> Piece::getGlobalPosition() const
{
    pair<int,int> position = this->getPosition();

    if(this->getColor() < 0) {
        // Black pieces at top of board
        position.second = 7 - position.second;
    } else {
        // White pieces at bottom of board
    }

    return position;
}

string Piece::getLetterPosition() const
{
    char xPos = static_cast<char>(this->getGlobalPosition().first+65);
    char yPos = static_cast<char>(this->getGlobalPosition().second+49);

    stringstream ss;
    ss << xPos << yPos;

    return ss.str();
}

void Piece::setPosition(const std::pair<int, int> & p)
{
    this->position = p;
}

string Piece::getType() const
{
    return this->type;
}

int Piece::getColor() const
{
    return this->color;
}



vector<pair<int,int> > Piece::movesOnBoard(vector<pair<int, int> > moves)
{
    vector<pair<int,int> > possibleMoves;

    for(auto &m : moves) {
        auto x = this->position.first + m.first;
        auto y = this->position.second + m.second;

        if(x>=0 && x<8 && y>=0 && y<8) {
            possibleMoves.push_back(pair<int,int>(x,y));
        }
    }

    return possibleMoves;
}

