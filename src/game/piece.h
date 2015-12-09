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

class Piece
{
public:
    // Constructor and destructor
    Piece(const int & x, const int & y, const enum PieceColor & c, const bool & hasMoved);
    virtual ~Piece();

    // Getters for type and color
    std::string getType() const;
    enum PieceColor getColor() const;

    // Getter for moves
    std::vector<Field> getMoves() const;

    // Getters for position
    Field getPosition() const;
    std::string getPositionString() const;

    // Obtain all possible moves
    virtual void findMoves(const std::vector<Piece*> & pieces) = 0;

    // Helper functions
    bool moveOnboard(const Field & m);
    std::vector<Field> movesOnboard(const std::vector<Field> &moves);

    // Perform move
    bool move(const Field & m);

    // Has to be false for Rook and King when castling
    bool hasMoved;

protected:
    // Type of piece
    std::string type;

    // Position on the board (dependent on color)
    Field position;

    // White or black?
    enum PieceColor color;

    // Possible moves; populated by findMoves()
    std::vector<Field> moves;

};

#endif // PIECE_H
