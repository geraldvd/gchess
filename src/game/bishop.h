#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece
{
public:
    Bishop(int x, int y, int c);

protected:
    void populateMoves();
};

#endif // BISHOP_H
