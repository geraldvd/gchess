#ifndef GAME_H
#define GAME_H

#include "field.h"
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "pawn.h"

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


private:
    // Vectors containing all chesspieces
    std::map<Field, Piece*> pieces;
    Piece* kingWhite;
    Piece* kingBlack;

    // Color to play
    enum PieceColor activePlayer;

};

#endif // GAME_H
