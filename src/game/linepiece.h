#ifndef LINEPIECE_H
#define LINEPIECE_H

#include "piece.h"

class LinePiece : public Piece
{
public:
    LinePiece(const int & x, const int & y, const enum PieceColor & c, const bool & hasMoved);

protected:
    virtual void findMoves(const std::vector<Piece*> & pieces);
};

#endif // LINEPIECE_H
