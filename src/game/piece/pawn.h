#ifndef PAWN_H
#define PAWN_H

// Include project files
#include "piece.h"

class Pawn : public Piece
{
public:
    Pawn(const PieceColor & c, const bool & hasMoved=false, const bool & justMovedDouble=false, Tile* parent=NULL);
    bool getJustMovedDouble() const;
    void setJustMovedDouble(const bool &d);

protected:
    virtual std::vector<Move> calculateMoves(Board *b);

    // Needed for En Passant moves
    bool justMovedDouble;
};

#endif // PAWN_H
