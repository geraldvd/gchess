#ifndef LINEPIECE_H
#define LINEPIECE_H

#include "piece.h"

class LinePiece : public Piece
{
public:
    LinePiece(const Field &f, const enum PieceColor & c, const bool & hasMoved);

protected:
    virtual std::vector<Field> getMoves(const std::map<Field,Piece*> &pieces, const bool &king_check);
    virtual std::vector<Field> getPotentialMoves();
};

#endif // LINEPIECE_H
