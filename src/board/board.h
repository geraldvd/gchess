#ifndef BOARD_H
#define BOARD_H

// Include standard libraries
#include <vector>

// Include project files
#include "../utils.h"
#include "field.h"
#include "tile.h"
#include "../piece/piece.h"

class Board
{
public:
    Board(const PieceColor &activePlayer=WHITE, const BoardStatus &bs=BS_NORMAL);

    // Tile methods
    Tile* getTile(const unsigned int &x, const unsigned int &y);
    Tile* getTile(const Field &f);
    std::vector<Tile*> getTiles();
    bool isOnBoard(const int &x, const int &y) const;

    // Piece methods
    std::vector<Piece_ptr> getPieces();
    void addPiece(const unsigned int &x, const unsigned int &y, const PieceType &type, const PieceColor &color);

    // Board status
    BoardStatus getBoardStatus() const;
    std::string getBoardStatusString() const;
    void setBoardStatus(const BoardStatus &bs);

    // Player methods
    PieceColor getActiveColor();
    std::string getActiveColorString() const;
    void setActiveColor(const PieceColor &color);
    void switchPlayer();

private:
    // Tiles on board
    std::vector<Tile> tiles;

    // Pieces on board
    std::vector<Piece_ptr> pieces;

    // Status of Kings on board
    BoardStatus board_status;

    // Player to move
    PieceColor activePlayer;
};

#endif // BOARD_H
