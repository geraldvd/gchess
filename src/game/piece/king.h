#ifndef KING_H
#define KING_H

// Include project files
#include "piece.h"

class King : public Piece
{
public:
    King(const enum PieceColor &c, const bool &has_moved=false, Tile* parent=NULL);

protected:
    virtual std::vector<Move> calculateMoves(Board * b);

private:

    // Castling variables - TODO smart pointers
    std::vector<Piece*> castlingRooks;
};

#endif // KING_H
