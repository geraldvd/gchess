#ifndef MOVE_H
#define MOVE_H

// Include project files
#include "utils.h"

// Forward declarations
class Board;

class Move : public Field
{
public:
    Move(const int &x, const int &y, const MoveType &mt=MT_NORMAL);
    Move(const int &m, const MoveType &mt=MT_NORMAL);

    // Move type methods
    MoveType getMoveType() const;
    void setMoveType(const MoveType &mt);
    void setValidity(const bool &valid);
    bool isValid() const;

    // Castling methods
    Field getCastlingRookPosition() const;
    void setCatlingRookPosition(const unsigned int &position);

    // Move execution
    bool execute(Board *b);

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
};

#endif // MOVE_H
