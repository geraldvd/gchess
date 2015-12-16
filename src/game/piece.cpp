#include "piece.h"

#include <sstream>
#include <algorithm>

using namespace std;

Piece::Piece(const Field &f, const PieceColor & c, const bool &has_moved) :
    position(f),
    color(c),
    has_moved(has_moved)
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

std::vector<Field> Piece::getMoves() const
{
    return this->moves;
}

Field Piece::getPosition() const
{
    return this->position;
}

string Piece::getPositionString() const
{
    return this->position.get();
}

bool Piece::moveOnboard(const Field &m)
{
    return (m.getX()>=0 && m.getX()<8 && m.getY()>=0 && m.getY()<8) ? true : false;
}


bool Piece::move(const Field &m)
{
    if(find(this->moves.begin(), this->moves.end(), m) != this->moves.end()) {
        // Move is in list of possible moves
        this->position = m;
        this->has_moved = true;
        return true;
    } else {
        // Move is not allowed!
        return false;
    }
}
