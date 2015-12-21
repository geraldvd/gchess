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
    Game(const PieceColor &active_player=WHITE);

    // Initializers
    void newGame(const int &game_type=1);
    void promotionTest();
    void castlingTest();
    void normalGame();

    // Getters
    Board* getBoard();
    PieceColor getActivePlayer() const;
    std::string getActivePlayerString() const;
    std::vector<Move> getMoves(const unsigned int &position) const;
    std::vector<unsigned int> getPositionsPossibleMoves(const unsigned int &position) const;

    // Move functions
    void updateAllMoves();
    MoveType move(const int &from, const int &to, const PromotionType &pt=PT_NONE);
    MoveType getMoveType(const int &from, const int &to);

private:
    Board board;

    // Color to play
    PieceColor activePlayer;

    // Possible moves
    std::map<unsigned int, std::vector<Move> > moves;
};

#endif // GAME_H
