#ifndef PLAYER_H
#define PLAYER_H

// Include standard libraries
#include <memory>
#include <map>

// Include project libraries
#include "../utils.h"

// Forward declarations
class Board;
class King;

class Player
{
public:
    /**
     * @brief Default constructor (Players must still be constructed by other constructor!)
     */
    Player();
    /**
     * @brief Constructor for player class. Board must be initialized before calling this.
     * @param Alliance of player (WHITE or BLACK)
     * @param Pointer to board.
     */
    Player(const PieceColor &color, Board* board);

    /**
     * @brief Getter for player alliance
     * @return WHITE or BLACK
     */
    PieceColor getColor() const;
    /**
     * @brief Getter for player alliance
     * @return "white" or "black" (string)
     */
    std::string getColorString() const;
    /**
     * @brief Setter for player alliance
     * @param WHITE or BLACK
     */
    void setColor(const PieceColor &color);
    /**
     * @brief Getter for board
     * @return Pointer to Board object
     */
    Board *getBoard();
    /**
     * @brief Getter for opponent
     * @return Pointer to Player object
     */
    Player* getOpponent();

    // Move methods

    /**
     * @brief Getter for possible moves, given that vector is filled before
     * @return Vector of Move objects
     */
    std::vector<Move> getMoves() const;


    // King methods
    /**
     * @brief Getter for king
     * @return std::shared_ptr to King object
     */
    std::shared_ptr<King> getKing();
    bool kingCheck();

    // Move methods


private:
    // Board playing on
    Board* board;

    // White or black player?
    PieceColor color;

    // Keep track of king
    std::shared_ptr<King> king;


};

#endif // PLAYER_H
