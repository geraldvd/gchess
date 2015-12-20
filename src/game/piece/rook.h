#ifndef ROOK_H
#define ROOK_H

// Include project files
#include "linepiece.h"

class Rook : public LinePiece
{
public:
    Rook(const enum PieceColor & c, const bool & hasMoved=false, Tile* parent=NULL);
};

#endif // ROOK_H
