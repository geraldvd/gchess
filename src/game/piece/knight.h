#ifndef KNIGHT_H
#define KNIGHT_H

// Include project files
#include "piece.h"

class Knight : public Piece
{
public:
    Knight(const unsigned int &position, const enum PieceColor &c, const bool &hasMoved=false);

protected:
    virtual std::vector<Move> calculateMoves(Board *b);
};

#endif // KNIGHT_H
