#include "rook.h"

using namespace std;

Rook::Rook(const int & x, const int & y, const PieceColor & c, const bool & hasMoved) :
    LinePiece(x, y, c, hasMoved)
{
    this->type = "Rook";
}

