#ifndef PAWN_H
#define PAWN_H

// Include project files
#include "piece.h"

class Pawn : public Piece
{
public:
    Pawn(const unsigned int &position, const enum PieceColor & c, const bool & hasMoved=false, const bool & justMovedDouble=false);

protected:
    virtual std::vector<unsigned int> calculateMoves(Board *b);

    // TODO needed for en passant capturing - https://en.wikipedia.org/wiki/En_passant
    bool justMovedDouble;
};

#endif // PAWN_H
