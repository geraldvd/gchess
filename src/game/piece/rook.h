#ifndef ROOK_H
#define ROOK_H

#include "linepiece.h"


class Rook : public LinePiece
{
public:
    Rook(const Field &f, const enum PieceColor & c, const bool & hasMoved=false);
};

#endif // ROOK_H
