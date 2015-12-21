// Include standard libraries
#include <stdexcept>
#include <sstream>

// Include project files
#include "tile.h"
#include "board/board.h"

// Specify namespaces
using namespace std;


Tile::Tile(const unsigned int &k)
{
    this->setPosition(k);
}

Tile::Tile(const unsigned int &x, const unsigned int &y)
{
    this->setPosition(x, y);
}

Tile::Tile(const string &s)
{
    this->setPositionString(s);
}

Tile::~Tile()
{
}

unsigned int Tile::getPosition() const
{
    //return this->x + 8*(7 - this->y);
    return this->x + 8*this->y;
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
    return this->x;
}

unsigned int Tile::getY() const
{
    return this->y;
}

Piece_ptr Tile::getPiece() const
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
        this->setX(k%8);
        this->setY((k-k%8)/8);
    } else {
        throw invalid_argument("k must be between 0 and 63.");
    }
}

void Tile::setPosition(const unsigned int &x, const unsigned int &y)
{
    this->setX(x);
    this->setY(y);
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
    if(x>=0 && x<8) {
        this->x = x;
    }
}

void Tile::setY(const unsigned int &y)
{
    if(y>=0 && y<8) {
        this->y = y;
    }
}

void Tile::setPiece(Piece_ptr p)
{
    this->piece = p;
    p->setTile(this);
}

void Tile::clearPiece()
{
    if(this->piece != NULL) {
        this->piece = NULL;
    }
}

bool Tile::tileUnderAttack(Board *b, const enum PieceColor &myColor)
{
    for(auto &p : b->getPieces()) {
        // Check whether field is empty OR has opposing color
        if(/*(this->isOccupied() && this->getPiece()->getColor() != p->getColor()) || */p->getColor() != myColor) {
            for(auto &m : p->calculateMoves(b)) {
                if(m.get() == this->getPosition()) {
                    return true;
                }
            }
        }
    }
    return false;
}
