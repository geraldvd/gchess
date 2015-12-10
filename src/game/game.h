#ifndef GAME_H
#define GAME_H

#include "piece.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "pawn.h"

#include <vector>
#include <utility>

class Game
{
public:
    // Constructor
    Game(const enum PieceColor & activePlayer=WHITE);
    ~Game();

    // Initialize chessboard
    void init();
    void initTest(); // TODO remove!

    // Methods for moves
    void updateAllMoves();
    bool move(Piece *p, const Move & m);

    // Getter and setter for pieces
    std::vector<Piece *> getPieces() const;
    void resetBoard();
    void addKing(const int & x, const int & y, const enum PieceColor & c, const bool & hasMoved=false);
    void addQueen(const int & x, const int & y, const enum PieceColor & c, const bool & hasMoved=false);
    void addRook(const int & x, const int & y, const enum PieceColor & c, const bool & hasMoved=false);
    void addKnight(const int & x, const int & y, const enum PieceColor & c, const bool & hasMoved=false);
    void addBishop(const int & x, const int & y, const enum PieceColor & c, const bool & hasMoved=false);
    void addPawn(const int & x, const int & y, const enum PieceColor & c, const bool & hasMoved=false, const bool & justMovedDouble=false);

    std::string getActivePlayerString() const;
    enum PieceColor getActivePlayer() const;

    // Check whether player is in check position
    int getPlayerCheck() const;

private:
    // Vectors containing all chesspieces
    std::vector<Piece*> pieces;

    // Color to play
    enum PieceColor activePlayer;

    // Player check?
    int playerCheck;

};

#endif // GAME_H
