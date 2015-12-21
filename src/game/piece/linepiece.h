#ifndef LINEPIECE_H
#define LINEPIECE_H

// Include project files
#include "piece.h"

class LinePiece : public Piece
{
public:
    LinePiece(const PieceType &type, const PieceColor & c, const bool & hasMoved, Tile* parent=NULL);

protected:
    virtual std::vector<Move> calculateMoves(Board *b);
};

#endif // LINEPIECE_H
