#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

// Include standard libraries
#include <utility>

// Include project files
#include "utils.h"
#include "board/board.h"
#include "engine/aiplayer.h"

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
    void enPassantTest();
    void staleMateTest();

    // Move
    MoveStatus move(const Field &from, const Field &to, const PromotionType &pt=PT_QUEEN);

    // Move history
    std::vector<std::pair<Move,std::string> > getMoveHistory() const;
    bool revertMove(const std::string &b);

private:
    Board board;

    // Move record
    std::vector<std::pair<Move,std::string> > moveHistory;
};

#endif // GAMEMANAGER_H
