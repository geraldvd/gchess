#include "rook.h"

using namespace std;

Rook::Rook(const PieceColor & c, const bool & hasMoved, Tile *parent) :
    LinePiece(ROOK, c, 5, hasMoved, parent)
{
}
