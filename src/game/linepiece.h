#ifndef LINEPIECE_H
#define LINEPIECE_H

#include "piece.h"

class LinePiece : public Piece
{
public:
    LinePiece(const Field &f, const enum PieceColor & c, const bool & hasMoved);

protected:
    virtual void findMoves(const std::map<Field,Piece*> &pieces);
};

#endif // LINEPIECE_H
