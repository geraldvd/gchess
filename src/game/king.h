#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece
{
public:
    King(const int & x, const int & y, const enum PieceColor & c, const bool & hasMoved=false);

protected:
    virtual void findMoves(const std::vector<Piece*> & pieces);
};

#endif // KING_H
