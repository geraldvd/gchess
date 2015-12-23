#ifndef KNIGHT_H
#define KNIGHT_H

// Include project files
#include "piece.h"

class Knight : public Piece
{
public:
    Knight(const PieceColor &c, const bool &hasMoved=false, Tile* parent=NULL);

protected:
    virtual std::vector<Move> calculateMoves(Board *b);
};

#endif // KNIGHT_H
