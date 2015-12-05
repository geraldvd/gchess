#include "piece.h"

#include <sstream>

using namespace std;

Piece::Piece(const int & x, const int & y, const Color & c, const bool & hasMoved) :
    hasMoved(hasMoved),
    position(Field(x,y)),
    color(c)
{
}

Piece::~Piece()
{

}

string Piece::getType() const
{
    return this->type;
}

Color Piece::getColor() const
{
    return this->color;
}

std::vector<Field> Piece::getMoves() const
{
    return this->moves;
}

Field Piece::getPosition() const
{
    return this->position;
}

string Piece::getLetterPosition() const
{
    // ASCII 65 == A; ASCII 49 == 1
    char xPos = static_cast<char>(this->getPosition().first+65);
    char yPos = static_cast<char>(this->getPosition().second+49);

    stringstream ss;
    ss << xPos << yPos;
    return ss.str();
}


bool Piece::moveOnboard(const Field & m)
{
    return (m.first>=0 && m.first<8 && m.second>=0 && m.second<8) ? true : false;
}

std::vector<Field> Piece::movesOnboard(const std::vector<Field> & moves)
{
    vector<Field> newMoves;

    for(auto &m : moves) {
        if(this->moveOnboard(m))
            newMoves.push_back(m);
    }

    return newMoves;
}




Field operator+(const Field & f1, const Field & f2)
{
    return Field(f1.first+f2.first, f1.second+f2.second);
}
