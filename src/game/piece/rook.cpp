#include "rook.h"

using namespace std;

Rook::Rook(const unsigned int &position, const PieceColor & c, const bool & hasMoved) :
    LinePiece(position, c, hasMoved)
{
    this->type = ROOK;
}
