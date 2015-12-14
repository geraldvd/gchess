#ifndef KING_H
#define KING_H

// Include standard libraries
#include <vector>

// Include project files
#include "piece.h"

class King : public Piece
{
public:
    King(const Field &f, const enum PieceColor &c, const bool &has_moved=false);

    // Perform move - castling is special case!
    virtual bool move(const Field &m);

private:
    virtual void findMoves(const std::map<Field,Piece*> &pieces);

    // Castling variables
    std::vector<Piece*> castlingRooks;
};

#endif // KING_H
