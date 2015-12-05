#ifndef QUEEN_H
#define QUEEN_H

#include "linepiece.h"

class Queen : public LinePiece
{
public:
    Queen(const int & x, const int & y, const enum Color & c, const bool & hasMoved=false);
};

#endif // QUEEN_H
