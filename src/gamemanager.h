#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

// Include standard libraries

// Include project files
#include "utils.h"
#include "board/board.h"
#include "board/move.h"


class GameManager
{
public:
    GameManager();

    // Get current gameboard
    Board* getBoard();

    // Move methods
    MoveStatus move(Move &m);
    MoveStatus move(const Field &from, const Field &to);

private:
    Board board;
};

#endif // GAMEMANAGER_H
