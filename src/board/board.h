#ifndef BOARD_H
#define BOARD_H

// Include standard libraries
#include <vector>

// Include project files
#include "../utils.h"
#include "field.h"
#include "tile.h"
#include "../piece/piece.h"
#include "../player/player.h"

class Board
{
public:
    Board(const PieceColor &activePlayer=WHITE, const BoardStatus &bs=BS_NORMAL);
    Board(const std::string & board);

    // Get total board in a single int
    std::string get() const;

    // Tile methods
    Tile* getTile(const unsigned int &x, const unsigned int &y);
    Tile* getTile(const Field &f);
    std::vector<Tile*> getTiles();
    bool isOnBoard(const int &x, const int &y) const;

    // Piece methods
    std::vector<Piece_ptr> getPieces();
    void addPiece(const unsigned int &x, const unsigned int &y, const PieceType &type, const PieceColor &color,
                  const bool & moved=false, const bool & justMovedDouble=false);
    std::shared_ptr<King> getActiveKing();
    std::shared_ptr<King> getInActiveKing();
    bool activeKingCheck() const;

    // Board status
    BoardStatus getBoardStatus() const;
    std::string getBoardStatusString() const;
    void setBoardStatus(const BoardStatus &bs);

    // Player methods
    PieceColor getActivePlayer() const;
    PieceColor getInActivePlayer() const;
    std::string getActivePlayerString() const;
    void setActivePlayer(const PieceColor &color);
    void switchPlayer();

    // Move methods
    void calculatePotentialMoves();
    Board move(Move &m);
    void updateMoves();
    std::vector<Move> getMoves() const;
    std::vector<Move> getPotentialMoves() const;


private:
    // Tiles on board
    std::vector<Tile> tiles;

    // Pieces on board
    std::vector<Piece_ptr> pieces;
    std::shared_ptr<King> whiteKing;
    std::shared_ptr<King> blackKing;

    // Status of Kings on board
    BoardStatus board_status;

    // Active player
    PieceColor activePlayer;

    // Possible moves
    std::vector<Move> moves;
    std::map<Move,std::string > boardsAfterMoves;
    std::vector<Move> potentialMoves;
};

#endif // BOARD_H
