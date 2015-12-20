#ifndef BISHOP_H
#define BISHOP_H

// Include project files
#include "linepiece.h"

class Bishop : public LinePiece
{
public:
    Bishop(const enum PieceColor & c, const bool & hasMoved=false, Tile* parent=NULL);
};

#endif // BISHOP_H
