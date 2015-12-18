#ifndef QUEEN_H
#define QUEEN_H

#include "linepiece.h"

class Queen : public LinePiece
{
public:
    Queen(const Field &f, const enum PieceColor & c, const bool & hasMoved=false);
};

#endif // QUEEN_H