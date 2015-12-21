// Include standard libraries
#include <sstream>

// Include project files
#include "utils.h"

// Specify namespaces
using namespace std;

int Field::getY() const {
    return this->y;
}

void Field::setY(const int &y) {
    this->y = y;
}

int Field::getPosition() const
{
    return this->x + 8*this->y;
}

std::string Field::getPositionString() const
{
    // ASCII 65 == A; ASCII 49 == 1
    char xPos = static_cast<char>(this->getX()+65);
    char yPos = static_cast<char>(this->getY()+49);

    stringstream ss;
    ss << xPos << yPos;
    return ss.str();
}

void Field::setPosition(const int &p)
{
    this->x = p%8;
    this->y = (p-p%8)/8;
}

void Field::setPosition(const int &x, const int &y)
{
    this->x = x;
    this->y = y;
}
Field::Field(const int &x, const int &y)
{
    this->setPosition(x, y);
}

Field::Field(const int &p)
{
    this->setPosition(p);
}

int Field::getX() const {
    return this->x;
}

void Field::setX(const int &x) {
    this->x = x;
}
