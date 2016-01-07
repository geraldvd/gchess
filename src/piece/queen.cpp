#include "queen.h"

using namespace std;

Queen::Queen(const PieceColor & c, const bool & hasMoved, Tile* parent) :
    LinePiece(QUEEN, c, 9, hasMoved, parent)
{
}

