#ifndef PLAYER_H
#define PLAYER_H

// Include standard libraries
#include <memory>

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
     * @brief Called at initialization and after move to find ALL possible next moves
     */
    void updateMoves();
    /**
     * @brief Getter for possible moves, given that vector is filled before
     * @return Vector of Move objects
     */
    std::vector<Move> getMoves() const;
    /**
     * @brief Perform actual move, given that this->moves is correctly filled
     * @param Move to be performed
     * @return MoveStatus: MS_OK, MS_INVALID or MS_PROMOTION (if so: call this->doPromotion)
     */
    MoveStatus move(const Move &m);
    /**
     * @brief Perform piece promotion, given that PromotionType is set in move variable
     * @param Move to be performed, with PromotionType as PT_QUEEN, PT_ROOK, PT_BISHOP, PT_KNIGHT
     * @return MoveStatus: MS_OK or MS_INVALID
     */
    MoveStatus doPromotion(const Move &m);

    // King methods
    /**
     * @brief Getter for king
     * @return std::shared_ptr to King object
     */
    std::shared_ptr<King> getKing();
    bool kingCheck();

private:
    // Move methods
    /**
     * @brief Calculate potential moves. Asked to individual pieces. Not yet accounting for board layout (e.g., check)
     * @return Vector of Move objects
     */
    std::vector<Move> getPotentialMoves();
    /**
     * @brief Returns true if castling move is valid (rook and king did not move, fields in between free, fields passed by king not under attack)
     * @param Move to be checked
     * @return true if castling is allowed
     */
    bool isCastling(const Move &m);
    /**
     * @brief Check whether a move will result in check (i.e., illegal move)
     * @param Move to be checked
     * @return True if it results in check
     */
    bool movingIntoCheck(const Move &m);
    /**
     * @brief Check whether move will solve a check position
     * @param Move to be checked
     * @return True if it does not result (i.e., solves) check
     */
    bool movingOutOfCheck(const Move &m);


private:
    // Board playing on
    Board* board;

    // White or black player?
    PieceColor color;

    // Keep track of king
    std::shared_ptr<King> king;

    // Possible moves
    std::vector<Move> moves;
};

#endif // PLAYER_H