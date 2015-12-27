// Include standard libraries
#include <sstream>
#include <stdexcept>
#include <iostream>

// Include project files
#include "field.h"
#include "../utils.h"

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

Field Field::string2field(const string &s)
{
    if(s.length() != 2) {
        throw invalid_argument("Coordinate must have 2 characters.");
    }


    int x = s.at(0) >= 'A' && s.at(0) <= 'Z' ? static_cast<int>(s.at(0)) - 'A' : static_cast<int>(s.at(0)) - 'a';
    int y = static_cast<int>(s.at(1)) - 49;

    if(x<0 || x>NUM_TILES_X-1 || y<0 || y>NUM_TILES_Y-1) {
        throw invalid_argument("Format: 'Xn', where X is a letter between A and H, and n is a number between 1 and 8.");
    }

    return Field(x,y);
}



Field::Field() :
    Field(0,0)
{

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
