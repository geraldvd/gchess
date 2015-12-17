#include "field.h"

// Include standard libraries
#include <stdexcept>
#include <sstream>

// Specify namespaces
using namespace std;

Field::Field(const string &f)
{
    this->set(f);
}

Field::Field(const unsigned int &x, const unsigned int &y)
{
    this->setX(x);
    this->setY(y);
}

unsigned int Field::getX() const
{
    return this->x;
}

unsigned int Field::getY() const
{
    return this->y;
}

string Field::get() const
{
    // ASCII 65 == A; ASCII 49 == 1
    char xPos = static_cast<char>(this->x+65);
    char yPos = static_cast<char>(this->y+49);

    stringstream ss;
    ss << xPos << yPos;
    return ss.str();
}

void Field::setX(const unsigned int &x)
{
    if(x>=0 && x<8) {
        this->x = x;
    } else {
        // Invalid
        throw invalid_argument("x must be between 0 (A) and 7 (H)");
    }
}

void Field::setY(const unsigned int &y)
{
    if(y>=0 && y<8) {
        this->y = y;
    } else {
        // Invalid
        throw invalid_argument("y must be between 0 and 7");
    }
}

void Field::set(const string &f)
{
    // Check length
    if(f.length() != 2) {
        // f must have 2 characters
        throw invalid_argument("Coordinate must have two characters");
    }

    // Set first character
    switch(f.at(0)) {
    case 'A':
        this->setX(0);
        break;
    case 'B':
        this->setX(1);
        break;
    case 'C':
        this->setX(2);
        break;
    case 'D':
        this->setX(3);
        break;
    case 'E':
        this->setX(4);
        break;
    case 'F':
        this->setX(5);
        break;
    case 'G':
        this->setX(6);
        break;
    case 'H':
        this->setX(7);
        break;
    default:
        throw invalid_argument("First character must be letter between A and H.");
        break;
    }

    // Set second character
    int y = static_cast<int>(f.at(1)) - 49;
    this->setY(y);
}

