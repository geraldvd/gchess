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

Field Piece::getPosition() const
{
    return this->position;
}

string Piece::getPositionString() const
{
    return this->position.get();
}

bool Piece::fieldUnderAttack(const Field &f, const map<Field,Piece*> &pieces)
{
    vector<Field> moves = this->getMoves(pieces, false);

    if(find(moves.begin(), moves.end(), f) != moves.end()) {
        return true;
    }

    return false;
}

bool Piece::moveOnboard(const Field &m)
{
    return (m.getX()>=0 && m.getX()<8 && m.getY()>=0 && m.getY()<8) ? true : false;
}


bool Piece::move(const Field &m, const map<Field,Piece*> &pieces, const bool &king_check)
{
    vector<Field> moves = this->getMoves(pieces, king_check);

    if(find(moves.begin(), moves.end(), m) != moves.end()) {
        // Move is in list of possible moves
        this->position = m;
        this->has_moved = true;
        return true;
    } else {
        // Move is not allowed!
        return false;
    }
}
