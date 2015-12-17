#include "queen.h"

using namespace std;

Queen::Queen(const Field &f, const PieceColor & c, const bool & hasMoved) :
    LinePiece(f, c, hasMoved)
{
    this->type = QUEEN;
}

