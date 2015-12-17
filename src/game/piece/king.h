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
    virtual bool move(const Field &m, const std::map<Field, Piece *> &pieces, const bool &king_check);

    // Obtain whether king is in check position
    bool checkStatus(const std::map<Field,Piece*> &pieces);

private:
    virtual std::vector<Field> getMoves(const std::map<Field,Piece*> &pieces, const bool &king_check);
    virtual std::vector<Field> getPotentialMoves();

    // Castling variables
    std::vector<Piece*> castlingRooks;
};

#endif // KING_H
