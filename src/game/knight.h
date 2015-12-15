#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece
{
public:
    Knight(const Field &f, const enum PieceColor & c, const bool & hasMoved=false);

protected:
    virtual void findMoves(const std::map<Field,Piece*> &pieces);
};

#endif // KNIGHT_H
