#ifndef GAME_H
#define GAME_H

// Include standard libraries
#include <string>

// Include project files
#include "board/board.h"

class Game
{
public:
    Game();

    void newGame();

    // Getters
    Board getBoard() const;
    enum PieceColor getActivePlayer() const;
    std::string getActivePlayerString() const;

private:
    Board board;

    // Color to play
    enum PieceColor activePlayer;
};

#endif // GAME_H
