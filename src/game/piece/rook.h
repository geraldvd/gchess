#ifndef ROOK_H
#define ROOK_H

// Include project files
#include "linepiece.h"

class Rook : public LinePiece
{
public:
    Rook(const unsigned int &position, const enum PieceColor & c, const bool & hasMoved=false);
};

#endif // ROOK_H
