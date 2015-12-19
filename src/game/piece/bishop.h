#ifndef BISHOP_H
#define BISHOP_H

// Include project files
#include "linepiece.h"

class Bishop : public LinePiece
{
public:
    Bishop(const unsigned int &position, const enum PieceColor & c, const bool & hasMoved=false);
};

#endif // BISHOP_H
