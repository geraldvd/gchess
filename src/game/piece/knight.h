#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece
{
public:
    Knight(const Field &f, const enum PieceColor & c, const bool & hasMoved=false);

protected:
    virtual std::vector<Field> getMoves(const std::map<Field,Piece*> &pieces, const bool &king_check);
    virtual std::vector<Field> getPotentialMoves();
};

#endif // KNIGHT_H
