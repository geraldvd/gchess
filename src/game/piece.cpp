#include "piece.h"

#include <sstream>
#include <algorithm>

using namespace std;

Piece::Piece(const int & x, const int & y, const PieceColor & c, const bool & hasMoved) :
    hasMoved(hasMoved),
    position(Field(x,y)),
    color(c),
    otherKingCheck(false)
{
}

Piece::~Piece()
{

}

PieceType Piece::getType() const
{
    return this->type;
}

PieceColor Piece::getColor() const
{
    return this->color;
}

string Piece::getColorString() const
{
    if(this->color == WHITE) {
        return string("white");
    } else {
        return string("black");
    }
}

std::vector<Move> Piece::getMoves() const
{
    return this->moves;
}

MoveType Piece::getMoveType() const
{
    return this->moveType;
}

bool Piece::isOtherKingCheck() const
{
    return this->otherKingCheck;
}

Field Piece::getPosition() const
{
    return this->position;
}

string Piece::getPositionString() const
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

bool Piece::move(const Move &m)
{
    if(find(this->moves.begin(), this->moves.end(), m) != this->moves.end()) {
        // Move is in list of possible moves
        this->position = m.first;
        this->hasMoved = true;
        this->moveType = NORMAL;
        return true;
    } else {
        // Move is not allowed!
        return false;
    }
}




Field operator+(const Field & f1, const Field & f2)
{
    return Field(f1.first+f2.first, f1.second+f2.second);
}

bool operator==(const Move &m1, const Move &m2)
{
    return m1.first==m2.first;
}

bool operator==(const Field &f1, const Field &f2)
{
    return f1.first==f2.first && f1.second==f2.second;
}

bool operator==(const Field &f, const Move &m)
{
    return f==m.first;
}

Move operator+(const Move &m, const Field &f)
{
    Move m2 = m;
    m2.first = m2.first + f;
    return m2;
}
