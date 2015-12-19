#ifndef KING_H
#define KING_H

// Include project files
#include "piece.h"

class King : public Piece
{
public:
    King(const unsigned int &position, const enum PieceColor &c, const bool &has_moved=false);

    // Obtain whether king is in check position
    bool checkStatus(Board *b);

protected:
    virtual std::vector<unsigned int> calculateMoves(Board * b);

private:

    // Castling variables
    std::vector<Piece*> castlingRooks;
};

#endif // KING_H
