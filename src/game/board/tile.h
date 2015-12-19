#ifndef TILE_H
#define TILE_H

// Include standard libraries
#include <utility>
#include <string>

// Include project files
#include "types.h"
#include "piece/piece.h"

// Forward declarations
class Piece;


class Tile
{
public:
    Tile(const unsigned int &k);
    Tile(const unsigned int &x, const unsigned int &y);
    Tile(const std::string &s);
    ~Tile();

    // Getters
    unsigned int getPosition() const;
    std::string getPositionString() const;
    unsigned int getX() const;
    unsigned int getY() const;
    Piece* getPiece() const;
    bool isOccupied() const;

    // Setters
    void setPosition(const unsigned int &k);
    void setPositionString(const std::string &s);
    void setX(const unsigned int &x);
    void setY(const unsigned int &y);
    void setPiece(Piece* p);
    void clearPiece();

private:
    // Field coordinates
    unsigned int position;

    // Piece
    Piece* piece;
};

#endif // TILE_H
