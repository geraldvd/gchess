#ifndef BOARD_H
#define BOARD_H

// Include standard libraries
#include <vector>

// Include project files
#include "utils.h"
#include "tile.h"
#include "piece/piece.h"
#include "player.h"

class Board
{
public:
    Board();

    // Initializers
    void initBoard(const int &board_layout=0);
    void standardBoard();
    void promotionTest();
    void castlingTest();

    // Tile methods
    Tile* getTile(const unsigned int &i);
    Tile* getTile(const unsigned int &x, const unsigned int &y);

    std::vector<Tile*> getTiles();
    std::vector<Piece_ptr> getPieces();
    bool isOnBoard(const int &i) const;
    bool isOnBoard(const int &x, const int &y) const;

    // Piece methods
    void addPiece(const unsigned int &position, const PieceType &type, const PieceColor &color);
    void addPiece(const unsigned int &x, const unsigned int &y, const PieceType &type, const PieceColor &color);
    void removePiece(const unsigned int &position);

private:
    // Tiles on board
    std::vector<Tile> tiles;

    // Status of Kings on board
    BoardStatus board_status;

    // Players
    Player whitePlayer;
    Player blackPlayer;
    PieceColor activePlayer;
};

#endif // BOARD_H
