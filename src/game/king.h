#ifndef KING_H
#define KING_H

#include <vector>

#include "piece.h"

class King : public Piece
{
public:
    King(const int & x, const int & y, const enum PieceColor & c, const bool & hasMoved=false);

    // Perform move - castling is special case!
    virtual bool move(const Move & m);

protected:
    virtual void findMoves(const std::vector<Piece*> & pieces);

    // Castling variables
    std::vector<Piece*> castlingRooks;
};

#endif // KING_H
