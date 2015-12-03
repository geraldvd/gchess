#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece
{
public:
    Knight(double x, double y);

protected:
    void populateMoves();
};

#endif // KNIGHT_H
