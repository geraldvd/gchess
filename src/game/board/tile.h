#ifndef TILE_H
#define TILE_H

// Include standard libraries
#include <utility>
#include <string>
#include <memory>

// Include project files
#include "types.h"
#include "piece/piece.h"

// Forward declarations
class Piece;
class Board;


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
    Piece_ptr getPiece() const;
    bool isOccupied() const;

    // Setters
    void setPosition(const unsigned int &k);
    void setPosition(const unsigned int &x, const unsigned int &y);
    void setPositionString(const std::string &s);
    void setX(const unsigned int &x);
    void setY(const unsigned int &y);
    void setPiece(Piece_ptr p);
    void clearPiece();

    bool tileUnderAttack(Board* b, const PieceColor &myColor);

private:
    // Field coordinates
    unsigned int x;
    unsigned int y;

    // Piece
    Piece_ptr piece;
};

#endif // TILE_H
