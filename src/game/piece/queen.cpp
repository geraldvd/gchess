#include "queen.h"

using namespace std;

Queen::Queen(const unsigned int &position, const PieceColor & c, const bool & hasMoved) :
    LinePiece(position, c, hasMoved)
{
    this->type = QUEEN;
}

