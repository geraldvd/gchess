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

    // Setters
    void setX(const unsigned int &x);
    void setY(const unsigned int &y);
    void set(const std::string &f);

    // Operators
    Field operator+(const Field &f);
    bool operator==(const Field &f) const;
    bool operator<(const Field &f) const;


private:
    // Field coordinates
    unsigned int x;
    unsigned int y;
};

#endif // FIELD_H
