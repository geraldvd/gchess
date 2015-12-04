#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece
{
public:
    King(int x, int y, int c);

protected:
    void findTheoreticalMoves();
};

#endif // KING_H
