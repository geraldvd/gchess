#include "queen.h"

using namespace std;

Queen::Queen(const PieceColor & c, const bool & hasMoved, Tile* parent) :
    LinePiece(c, hasMoved, parent)
{
    this->type = QUEEN;
}

