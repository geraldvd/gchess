#ifndef GAME_H
#define GAME_H

// Include standard libraries
#include <string>
#include <vector>
#include <map>

// Include project files
#include "board/board.h"
#include "board/move.h"

class Game
{
public:
    Game();

    // Get current gameboard
    Board* getBoard();

    // Move functions
    void updateAllMoves();
    std::vector<Move> getMoves(const unsigned int &position) const;
    std::vector<unsigned int> getPositionsPossibleMoves(const unsigned int &position) const;
    MoveType move(const int &from, const int &to, const PromotionType &pt=PT_NONE);
    MoveType getMoveType(const int &from, const int &to);

private:
    Board board;

    // Possible moves
    std::map<unsigned int, std::vector<Move> > moves;
};

#endif // GAME_H
