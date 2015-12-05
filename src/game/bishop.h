#ifndef BISHOP_H
#define BISHOP_H

#include "linepiece.h"

class Bishop : public LinePiece
{
public:
    Bishop(const int & x, const int & y, const enum Color & c, const bool & hasMoved=false);
};

#endif // BISHOP_H
