#include "bishop.h"

using namespace std;

Bishop::Bishop(const int & x, const int & y, const PieceColor & c, const bool & hasMoved) :
    LinePiece(x, y, c, hasMoved)
{
    this->type = BISHOP;
}
