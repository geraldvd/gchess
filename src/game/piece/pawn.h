#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece
{
public:
    Pawn(const Field &f, const enum PieceColor & c, const bool & hasMoved=false, const bool & justMovedDouble=false);

protected:
    virtual std::vector<Field> getMoves(const std::map<Field,Piece*> &pieces, const bool &king_check);
    virtual std::vector<Field> getPotentialMoves();

    // TODO needed for en passant capturing - https://en.wikipedia.org/wiki/En_passant
    bool justMovedDouble;
};

#endif // PAWN_H
