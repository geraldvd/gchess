#ifndef QUEEN_H
#define QUEEN_H

// Include project files
#include "linepiece.h"

class Queen : public LinePiece
{
public:
    Queen(const unsigned int &position, const enum PieceColor & c, const bool & hasMoved=false);
};

#endif // QUEEN_H
