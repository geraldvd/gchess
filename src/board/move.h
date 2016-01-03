#ifndef MOVE_H
#define MOVE_H

// Include project files
#include "../utils.h"
#include "field.h"

// Forward declarations
class Board;

class Move
{
public:
    Move();
    Move(const Field &f, Piece_ptr movingPiece, const MoveType &mt=MT_NORMAL, const PromotionType &pt=PT_NONE);
    Move(const int &x, const int &y, Piece_ptr movingPiece, const MoveType &mt=MT_NORMAL, const PromotionType &pt=PT_NONE);

    // Move type methods
    MoveType getMoveType() const;
    void setMoveType(const MoveType &mt);

    // Moving piece
    Piece_ptr getMovingPiece() const;

    // Destination
    Field getDestination() const;

    // Extra information
    Field getCastlingRookPosition() const;
    PromotionType getPromotionType() const;
    void setCastlingRookPosition(const Field &position);
    void setPromotionType(const PromotionType &pt);

    // Move execution
    Board execute(Board * b);

    // Hash for comparison
    unsigned int getHash() const;

    // Pretty representation
    std::string getMoveString() const;
private:
    // Basic move information
    MoveType moveType;
    Piece_ptr movingPiece;
    Field destination;

    // Extra information
    Field castlingRookPosition;
    PromotionType promotionType;
};

#endif // MOVE_H
