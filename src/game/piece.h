#ifndef PIECE_H
#define PIECE_H

#include <utility>
#include <vector>
#include <string>

// Typedef for chess field
typedef std::pair<int,int> Field;
Field operator+(const Field & f1, const Field & f2);

// Piece type
enum PieceType {KING, QUEEN, ROOK, KNIGHT, BISHOP, PAWN};

// Color type
enum PieceColor {WHITE, BLACK};

// Move type
enum MoveType {NORMAL, CASTLING, CHECK, ENPASSANT};

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
    std::vector<Field> getMoves() const;
    enum MoveType getMoveType() const;

    // Getters for position
    Field getPosition() const;
    std::string getPositionString() const;

    // Obtain all possible moves
    virtual void findMoves(const std::vector<Piece*> & pieces) = 0;

    // Helper functions
    bool moveOnboard(const Field & m);
    std::vector<Field> movesOnboard(const std::vector<Field> &moves);

    // Perform move
    virtual bool move(const Field & m);

    // Has to be false for Rook and King when castling
    bool hasMoved;
    enum MoveType moveType;

protected:
    // Type of piece
    enum PieceType type;

    // Position on the board (dependent on color)
    Field position;

    // White or black?
    enum PieceColor color;

    // Possible moves; populated by findMoves()
    std::vector<Field> moves;

};

#endif // PIECE_H
