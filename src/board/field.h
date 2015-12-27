#ifndef FIELD_H
#define FIELD_H

// Include standard libraries
#include <string>


class Field {
    int x;
    int y;
public:
    // Constructors
    Field();
    Field(const int &x, const int &y);
    Field(const int &p);

    // Getters and setters
    int getX() const;
    void setX(const int &x);
    int getY() const;
    void setY(const int &y);
    int getPosition() const;
    std::string getPositionString() const;
    void setPosition(const int &p);
    void setPosition(const int &x, const int &y);

    // Static methods
    static Field string2field(const std::string &s);
};
#endif // FIELD_H
