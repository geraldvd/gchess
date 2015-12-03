#ifndef ROOK_H
#define ROOK_H

#include "piece.h"


class Rook : public Piece
{
public:
    Rook(int x, int y);

protected:
    void populateMoves();
};

#endif // ROOK_H
