#ifndef QUEEN_H
#define QUEEN_H

// Include project files
#include "linepiece.h"

class Queen : public LinePiece
{
public:
    Queen(const enum PieceColor & c, const bool & hasMoved=false, Tile *parent=NULL);
};

#endif // QUEEN_H
