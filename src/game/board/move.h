#ifndef MOVE_H
#define MOVE_H

// Include project files
#include "types.h"

class Move
{
public:
    Move(const int &x, const int &y, const enum MoveType &mt=MT_NONE);
    Move(const unsigned int &old_position, const std::pair<unsigned int, unsigned int> &move, const enum MoveType &mt=MT_NONE);

    // Getters
    int getX() const;
    int getY() const;
    enum MoveType getMoveType() const;

    // Setters
    void setX(const int &x);
    void setY(const int &y);
    void setMoveType(const enum MoveType &mt);


private:
    // Move type
    enum MoveType move_type;

    // Move coordinates
    unsigned int position;
};

#endif // MOVE_H
