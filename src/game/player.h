#ifndef PLAYER_H
#define PLAYER_H

// Include standard libraries
#include <memory>

// Include project libraries
#include "utils.h"

// Forward declarations
class Board;
class King;

class Player
{
public:
    Player();
    Player(const PieceColor &color, Board* board);

    PieceColor getColor() const;
    void setColor(const PieceColor &color);
    Board *getBoard();

private:
    PieceColor color;
    Board* board;
    std::shared_ptr<King> king;
};

#endif // PLAYER_H
