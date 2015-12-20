#ifndef PIECE_H
#define PIECE_H

// Include standard libraries
#include <utility>
#include <vector>
#include <string>
#include <map>

// Include project files
#include "operators.h"
//#include "board/board.h"

// Forward declarations
class Board;

class Piece
{
public:
    // Constructor and destructor
    Piece(const unsigned int &position, const enum PieceColor &c, const bool &has_moved);
    virtual ~Piece();

    // Getters
    unsigned int getPosition() const;
    enum PieceType getType() const;
    std::string getTypeString() const;
    enum PieceColor getColor() const;
    std::string getColorString() const;

    // Move methods
    virtual std::vector<Move> calculateMoves(Board *b) = 0;

protected:
    // Position of piece
    unsigned int position;

    // Type of piece
    enum PieceType type;

    // White or black?
    enum PieceColor color;

    // Has to be false for Rook and King when castling
    bool has_moved;
};

#endif // PIECE_H
