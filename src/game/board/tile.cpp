#include "tile.h"

// Include standard libraries
#include <stdexcept>
#include <sstream>

// Specify namespaces
using namespace std;


Tile::Tile(const unsigned int &k) :
    piece(NULL)
{
    this->setPosition(k);
}

Tile::Tile(const unsigned int &x, const unsigned int &y) :
    Tile(x+8*y)
{
}

Tile::Tile(const string &s) :
    piece(NULL)
{
    this->setPositionString(s);
}

Tile::~Tile()
{
        this->clearPiece();
}

unsigned int Tile::getPosition() const
{
    return this->position;
}

string Tile::getPositionString() const
{
    // ASCII 65 == A; ASCII 49 == 1
    char xPos = static_cast<char>(this->getX()+65);
    char yPos = static_cast<char>(this->getY()+49);

    stringstream ss;
    ss << xPos << yPos;
    return ss.str();
}

unsigned int Tile::getX() const
{
    return this->position % 8;
}

unsigned int Tile::getY() const
{
    return (this->position - this->getX()) / 8;
}

Piece *Tile::getPiece() const
{
    return this->piece;
}

bool Tile::isOccupied() const
{
    if(this->piece == NULL) {
        return false;
    }

    return true;
}

void Tile::setPosition(const unsigned int &k)
{
    if(k>=0 || k<64) {
        this->position = k;
    } else {
        throw invalid_argument("k must be between 0 and 63.");
    }
}

void Tile::setPositionString(const string &s)
{
    // Check length
    if(s.length() != 2) {
        // f must have 2 characters
        throw invalid_argument("Coordinate must have two characters");
    }

    // Set first character
    switch(s.at(0)) {
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
    unsigned int y = static_cast<int>(s.at(1)) - 49;
    this->setY(y);
}

void Tile::setX(const unsigned int &x)
{
    // Substitute old x value
    unsigned int old_x = this->getX();
    this->position += (x - old_x);

    // Check new position (set position contains exception handling)
    this->setPosition(this->getPosition());
}

void Tile::setY(const unsigned int &y)
{
    unsigned int x = this->getX();
    this->setPosition(x + 8*y);
}

void Tile::setPiece(Piece *p)
{
    this->clearPiece();
    this->piece = p;
}

void Tile::clearPiece()
{
    if(this->piece != NULL) {
        // TODO who clears memory?
        delete this->piece;
        this->piece = NULL;
    }
}
