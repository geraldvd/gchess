#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece
{
public:
    Knight(int x, int y, int c);

protected:
    void findTheoreticalMoves();
};

#endif // KNIGHT_H
