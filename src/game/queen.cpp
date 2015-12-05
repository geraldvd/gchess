#include "queen.h"

using namespace std;

Queen::Queen(const int & x, const int & y, const Color & c, const bool & hasMoved) :
    LinePiece(x, y, c, hasMoved)
{
    this->type = "Queen";
}

