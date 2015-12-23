#include "bishop.h"

using namespace std;

Bishop::Bishop(const PieceColor & c, const bool & hasMoved, Tile* parent) :
    LinePiece(BISHOP, c, hasMoved, parent)
{
}
