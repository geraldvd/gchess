#ifndef FIELD_H
#define FIELD_H

// Include standard libraries
#include <string>


class Field {
    int x;
    int y;
public:
    // Constructors
    Field(const int &x, const int &y);
    Field(const int &p);

    // Getters
    int getX() const;
    int getY() const;
    int getPosition() const;
    std::string getPositionString() const;

    // Setters
    void setX(const int &x);
    void setY(const int &y);
    void setPosition(const int &x, const int &y);
    void setPosition(const int &p);

    // Static methods
    static Field string2field(const std::string &s);

    // Hash for comparison
    unsigned int getHash() const;
};
#endif // FIELD_H
