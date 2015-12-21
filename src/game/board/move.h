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

    // Castling methods
    unsigned int getCastlingRookPosition() const;
    void setCatlingRookPosition(const unsigned int &position);

    // Move execution
    bool execute(Board *b);

private:
    // Move type
    MoveType move_type;

    // Extra information
    unsigned int castlingRookPosition;
};

#endif // MOVE_H
