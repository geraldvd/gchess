#ifndef MOVE_H
#define MOVE_H

// Include project files
#include "../utils.h"

// Forward declarations
class Board;

class Move : public Field
{
public:
    Move();
    Move(const int &x, const int &y, Piece_ptr movingPiece, const MoveType &mt=MT_NORMAL, const PromotionType &pt=PT_NONE);
    Move(const int &m, Piece_ptr movingPiece, const MoveType &mt=MT_NORMAL);

    // Move type methods
    MoveType getMoveType() const;
    void setMoveType(const MoveType &mt);
    void setValidity(const bool &valid);
    bool isValid() const;

    // Extra information methods
    Field getCastlingRookPosition() const;
    void setCatlingRookPosition(const Field &position);
    PromotionType getPromotionType() const;
    void setPromotionType(const PromotionType &pt);

    // Moving piece
    Piece_ptr getMovingPiece() const;

private:
    // Move type
    MoveType moveType;
    bool moveValid;

    // Moving piece
    Piece_ptr movingPiece;

    // Extra information
    Field castlingRookPosition;
    PromotionType promotionType;
};

#endif // MOVE_H
