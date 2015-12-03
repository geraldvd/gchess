#ifndef GAME_H
#define GAME_H

#include "piece.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "pawn.h"

#include <vector>
#include <utility>

class Game
{
public:
    Game();

    void init();

    bool isValidMove(Piece * p, std::pair<int,int> m);
    std::vector<std::pair<double,double> > getMoves(Piece * p) const;

    void addWhitePiece(Piece* p);
    void addBlackPiece(Piece* p);

private:
    std::vector<Piece*> white;
    std::vector<Piece*> black;

};

#endif // GAME_H
