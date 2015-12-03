#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"


class Queen : public Piece
{
public:
    Queen(int x, int y);

protected:
    void populateMoves();
};

#endif // QUEEN_H
