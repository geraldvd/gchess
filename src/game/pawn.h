#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece
{
public:
    Pawn(const int & x, const int & y, const enum PieceColor & c, const bool & hasMoved=false, const bool & justMovedDouble=false);

protected:
    virtual void findMoves(const std::vector<Piece*> & pieces);

    // TODO needed for en passant capturing - https://en.wikipedia.org/wiki/En_passant
    bool justMovedDouble;
};

#endif // PAWN_H
