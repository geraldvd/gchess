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
    std::string getColorString() const;
    void setColor(const PieceColor &color);
    Board *getBoard();

    // Move methods
    void updateMoves();
    std::vector<Move> getMoves() const;
    MoveType move(const Field &from, const Field &to, const PromotionType &pt=PT_NONE);

    // King methods
    std::shared_ptr<King> getKing();
    bool kingCheck() const;

private:
    // Move methods
    std::vector<Move> getPossibleMoves();
    std::vector<Move> getPotentialMoves();
    bool isCastling(const Move &m);


private:
    // Board playing on
    Board* board;

    // White or black player?
    PieceColor color;

    // Keep track of king
    std::shared_ptr<King> king;

    // Possible moves
    std::vector<Move> moves;
};

#endif // PLAYER_H
