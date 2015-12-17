#ifndef GAME_H
#define GAME_H

#include "field.h"
#include "piece/piece.h"
#include "piece/king.h"
#include "piece/queen.h"
#include "piece/rook.h"
#include "piece/knight.h"
#include "piece/bishop.h"
#include "piece/pawn.h"

#include <vector>
#include <utility>
#include <map>

class Game
{
public:
    // Constructor
    Game(const bool & normal_game=true, const enum PieceColor & active_player=WHITE);
    ~Game();

    // Initialize chessboard
    void init();
//    // TODO add function to check validity of positions + function to add custom positions
    void initTest(); // TODO remove!

    // Methods for moves
    void updateAllMoves();
    bool move(Piece *p, const Field & m);

    // Getter and setter for pieces
    void resetBoard();
    void addPiece(const enum PieceType &t, const Field &f, const enum PieceColor &c, const bool &has_moved=false, const bool &just_moved_double=false);

    std::string getActivePlayerString() const;
    enum PieceColor getActivePlayer() const;
    Piece* getPiece(const Field &f) const;

    // Check whether player is in check position
    bool isCurrentPlayerCheck() const;

private:
    // Vectors containing all chesspieces
    std::map<Field, Piece*> pieces;
    King* whiteKing;
    King* blackKing;

    // Color to play
    enum PieceColor activePlayer;
    bool currentPlayerCheck;


};

#endif // GAME_H
