#ifndef KING_H
#define KING_H

// Include project files
#include "piece.h"

class King : public Piece
{
public:
    King(const PieceColor &c, const bool &has_moved=false, Tile* parent=NULL);

protected:
    virtual std::vector<Move> calculateMoves(Board * b);
};

#endif // KING_H
