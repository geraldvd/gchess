#ifndef BISHOP_H
#define BISHOP_H

#include "linepiece.h"

class Bishop : public LinePiece
{
public:
    Bishop(const int & x, const int & y, const enum PieceColor & c, const bool & hasMoved=false);
};

#endif // BISHOP_H
