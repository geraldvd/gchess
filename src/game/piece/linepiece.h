#ifndef LINEPIECE_H
#define LINEPIECE_H

// Include project files
#include "piece.h"

class LinePiece : public Piece
{
public:
    LinePiece(const unsigned int &position, const enum PieceColor & c, const bool & hasMoved);

protected:
    virtual std::vector<Move> calculateMoves(Board *b);
};

#endif // LINEPIECE_H
