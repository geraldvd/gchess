#ifndef PAWN_H
#define PAWN_H

// Include project files
#include "piece.h"

class Pawn : public Piece
{
public:
    Pawn(const PieceColor & c, const bool & justMovedDouble=false, const bool & hasMoved=false, Tile* parent=NULL);

protected:
    virtual std::vector<Move> calculateMoves(Board *b);
};

#endif // PAWN_H
