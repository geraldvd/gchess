#ifndef BOARD_H
#define BOARD_H

// Include standard libraries
#include <vector>

// Include project files
#include "types.h"
#include "tile.h"
#include "piece/piece.h"

class Board
{
public:
    Board();

    // Getters
    Tile* getTile(const unsigned int &i);
    std::vector<Tile *> getTiles();
    std::vector<Piece*> getPieces();
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
