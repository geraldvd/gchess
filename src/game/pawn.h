#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece
{
public:
    Pawn(int x, int y, int c);

protected:
    void populateMoves();
};

#endif // PAWN_H
