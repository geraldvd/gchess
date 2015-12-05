#ifndef ROOK_H
#define ROOK_H

#include "linepiece.h"


class Rook : public LinePiece
{
public:
    Rook(const int & x, const int & y, const enum Color & c, const bool & hasMoved=false);
};

#endif // ROOK_H
