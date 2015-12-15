#include "rook.h"

using namespace std;

Rook::Rook(const Field &f, const PieceColor & c, const bool & hasMoved) :
    LinePiece(f, c, hasMoved)
{
    this->type = ROOK;
}

