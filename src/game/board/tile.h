#ifndef TILE_H
#define TILE_H

// Include standard libraries
#include <utility>
#include <string>

// Include project files
#include "../types.h"
#include "../piece/piece.h"


class Tile
{
public:
    Tile(const unsigned int &k);
    ~Tile();

    // Getters
    Field getField() const;
    bool isOccupied() const;

    // Setters
    void setField(const unsigned int &k);
    void setPiece(Piece* p);
    void clearPiece();

private:
    // Field coordinates
    int position;

    // Piece
    Piece* piece;
};

#endif // TILE_H
