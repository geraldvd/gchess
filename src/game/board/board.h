#ifndef BOARD_H
#define BOARD_H

// Include standard libraries
#include <vector>

// Include project files
#include "types.h"
#include "tile.h"

class Board
{
public:
    Board();

    // Getters
    Tile getTile(const unsigned int &i) const;
    bool isOnBoard(const unsigned int &i) const;

    // Piece methods
    void addPiece(const unsigned int &position, const enum PieceType &type, const enum PieceColor &color);
    void removePiece(const unsigned int &position);

private:
    std::vector<Tile> tiles;

    enum BoardStatus board_status;

public:
    // Constants
    static const unsigned int NUM_TILES{64};

};

#endif // BOARD_H
