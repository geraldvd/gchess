#ifndef ROOK_H
#define ROOK_H

#include "piece.h"


class Rook : public Piece
{
public:
    Rook(int x, int y, int c);

protected:
    void populateMoves();
};

#endif // ROOK_H
