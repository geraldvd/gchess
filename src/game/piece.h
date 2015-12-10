#ifndef PIECE_H
#define PIECE_H

#include <utility>
#include <vector>
#include <string>


// Piece type
enum PieceType {KING, QUEEN, ROOK, KNIGHT, BISHOP, PAWN};

// Color type
enum PieceColor {WHITE=1, BLACK=-1};

// Move type
enum MoveType {NORMAL, CASTLING, ENPASSANT, PROMOTION_QUEEN, PROMOTION_ROOK, PROMOTION_KNIGHT, PROMOTION_BISHOP};

// Typedef for chess field
typedef std::pair<int,int> Field;
typedef std::pair<Field,enum MoveType> Move;
Field operator+(const Field & f1, const Field & f2);
Move operator+(const Move & m, const Field & f);
bool operator==(const Field & f1, const Field & f2);
bool operator==(const Move & m1, const Move & m2);
bool operator==(const Field & f, const Move & m);


class Piece
{
public:
    // Constructor and destructor
    Piece(const int & x, const int & y, const enum PieceColor & c, const bool & hasMoved);
    virtual ~Piece();

    // Getters for type and color
    enum PieceType getType() const;
    enum PieceColor getColor() const;
    std::string getColorString() const;

    // Getter for moves
    std::vector<Move> getMoves() const;
    enum MoveType getMoveType() const;
    bool isOtherKingCheck() const;

    // Getters for position
    Field getPosition() const;
    std::string getPositionString() const;

    // Obtain all possible moves
    virtual void findMoves(const std::vector<Piece*> & pieces) = 0;

    // Helper functions
    bool moveOnboard(const Field & m);
    std::vector<Field> movesOnboard(const std::vector<Field> &moves);

    // Perform move
    virtual bool move(const Move &m);

    // Has to be false for Rook and King when castling
    bool hasMoved;

protected:
    // Type of piece
    enum PieceType type;

    // Position on the board (dependent on color)
    Field position;

    // White or black?
    enum PieceColor color;

    // Possible moves; populated by findMoves()
    std::vector<Move> moves;
    enum MoveType moveType;

    // Is the king of the other team in check position?
    bool otherKingCheck;
};

#endif // PIECE_H
