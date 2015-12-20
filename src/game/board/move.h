#ifndef MOVE_H
#define MOVE_H

// Include project files
#include "types.h"

class Move
{
public:
    Move(const int &x, const int &y, const enum MoveType &mt=MT_NONE);
    Move(const unsigned int &m, const enum MoveType &mt=MT_NONE);

    // Getters
    unsigned int get() const;
    unsigned int getX() const;
    unsigned int getY() const;
    enum MoveType getMoveType() const;

    // Setters
    void set(const unsigned int &m);
    void setX(const unsigned int &x);
    void setY(const unsigned int &y);
    void setMoveType(const enum MoveType &mt);


private:
    // Move type
    enum MoveType move_type;

    // Move coordinates
    unsigned int destination;
};

#endif // MOVE_H
