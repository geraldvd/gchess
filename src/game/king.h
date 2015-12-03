#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece
{
public:
    King(int x, int y);

protected:
    void populateMoves();
};

#endif // KING_H
