#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

// Include standard libraries

// Include project files
#include "utils.h"
#include "board/board.h"
#include "player/player.h"


class GameManager
{
public:
    GameManager(const int &board_layout=0);

    // Get current gameboard
    Board* getBoard();

    // Board creators
    void initBoard(const int &board_layout);
    void standardBoard();
    void promotionTest();
    void castlingTest();
    void movingInCheckTest();
    void moveOutCheckTest();
    void moveOutCheckTest2();

    // Move
    MoveStatus move(const Field &from, const Field &to);

private:
    Board board;
};

#endif // GAMEMANAGER_H
