#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece
{
public:
    Knight(const int & x, const int & y, const enum PieceColor & c, const bool & hasMoved=false);

protected:
    virtual void findMoves(const std::vector<Piece*> & pieces);
};

#endif // KNIGHT_H
