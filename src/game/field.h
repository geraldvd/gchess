#ifndef FIELD_H
#define FIELD_H

// Include standard libraries
#include <utility>
#include <string>

// Include project files
#include "types.h"


class Field
{
public:
    Field(const std::string & f);
    Field(const unsigned int &x, const unsigned int &y);

    // Getters
    unsigned int getX() const;
    unsigned int getY() const;
    std::string get() const;
    enum MoveType getMoveType() const;

    // Setters
    void setX(const unsigned int &x);
    void setY(const unsigned int &y);
    void set(const std::string &f);
    void setMoveType(const enum MoveType &mt);

    // Operators
    friend Field operator+(const Field & f1, const Field & f2);
    friend bool operator==(const Field & f1, const Field & f2);

private:
    // Field coordinates
    unsigned int x;
    unsigned int y;

    // Move variables
    enum MoveType move_type;
};

#endif // FIELD_H
