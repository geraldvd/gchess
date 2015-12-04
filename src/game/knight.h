#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece
{
public:
    Knight(int x, int y, int c);

protected:
    void populateMoves();
};

#endif // KNIGHT_H
