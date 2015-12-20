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
    Game(const enum PieceColor &active_player=WHITE);

    void newGame();

    // Getters
    Board* getBoard();
    enum PieceColor getActivePlayer() const;
    std::string getActivePlayerString() const;
    std::vector<Move> getMoves(const unsigned int &position) const;
    std::vector<unsigned int> getPositionsPossibleMoves(const unsigned int &position) const;

    // Move functions
    void updateAllMoves();
    enum MoveType move(const unsigned int &from, const unsigned int &to);

private:
    Board board;

    // Color to play
    enum PieceColor activePlayer;

    // Possible moves
    std::map<unsigned int, std::vector<Move> > moves;
};

#endif // GAME_H
