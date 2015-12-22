#ifndef BOARD_H
#define BOARD_H

// Include standard libraries
#include <vector>

// Include project files
#include "utils.h"
#include "tile.h"
#include "piece/piece.h"
#include "player/player.h"

class Board
{
public:
    Board(const int &board_layout=0);

    // Initializers
    void initBoard(const int &board_layout);
    void standardBoard();
    void promotionTest();
    void castlingTest();

    // Tile methods
    Tile* getTile(const Field &f);
    Tile* getTile(const unsigned int &i);
    Tile* getTile(const unsigned int &x, const unsigned int &y);
    std::vector<Tile*> getTiles();
    bool isOnBoard(const int &i) const;
    bool isOnBoard(const int &x, const int &y) const;

    // Piece methods
    std::vector<Piece_ptr> getPieces();
    void addPiece(const unsigned int &position, const PieceType &type, const PieceColor &color);
    void addPiece(const unsigned int &x, const unsigned int &y, const PieceType &type, const PieceColor &color);
    void removePiece(const unsigned int &position);

    // Player methods
    Player* getActivePlayer();
    void switchPlayer();

    // Board status
    BoardStatus getBoardStatus() const;
    std::string getBoardStatusString() const;

    // Move method
    bool move(const Field &from, const Field &to, const PromotionType &pt=PT_NONE);

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
