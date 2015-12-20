#ifndef PAWN_H
#define PAWN_H

// Include project files
#include "piece.h"

class Pawn : public Piece
{
public:
    Pawn(const unsigned int &position, const enum PieceColor & c, const bool & hasMoved=false, const bool & justMovedDouble=false);
    bool getJustMovedDouble() const;

protected:
    virtual std::vector<Move> calculateMoves(Board *b);

    // Needed for En Passant moves
    bool justMovedDouble;
};

#endif // PAWN_H
