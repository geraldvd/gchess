#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

// Include standard libraries

// Include project files
#include "utils.h"
#include "board/board.h"


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
    void enPassantTest();
    void staleMateTest();

    // Move
    MoveStatus move(const Field &from, const Field &to, const PromotionType &pt=PT_QUEEN);

private:
    Board board;
};

#endif // GAMEMANAGER_H
