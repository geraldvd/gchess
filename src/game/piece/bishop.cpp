#include "bishop.h"

using namespace std;

Bishop::Bishop(const unsigned int &position, const PieceColor & c, const bool & hasMoved) :
    LinePiece(position, c, hasMoved)
{
    this->type = BISHOP;
}
