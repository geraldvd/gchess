#ifndef PIECE_H
#define PIECE_H

// Include standard libraries
#include <utility>
#include <vector>
#include <string>
#include <map>

// Include project files
#include "board/field.h"
#include "operators.h"
#include "board/move.h"

// Forward declarations
class Board;

class Piece
{
public:
    // Constructor and destructor
    Piece(const enum PieceColor &c, const bool &has_moved);
    virtual ~Piece();

    // Getters
    enum PieceType getType() const;
    enum PieceColor getColor() const;
    std::string getColorString() const;

    // Move methods
    virtual std::vector<Move> calculateMoves(const Board * const b) = 0;

protected:
    // Type of piece
    enum PieceType type;

    // White or black?
    enum PieceColor color;

    // Has to be false for Rook and King when castling
    bool has_moved;
};

#endif // PIECE_H
