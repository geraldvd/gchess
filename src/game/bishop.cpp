#include "bishop.h"

using namespace std;

Bishop::Bishop(const Field &f, const PieceColor & c, const bool & hasMoved) :
    LinePiece(f, c, hasMoved)
{
    this->type = BISHOP;
}
