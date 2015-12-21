#ifndef PIECE_H
#define PIECE_H

// Include standard libraries
#include <vector>
#include <string>

// Include project files
#include "operators.h"

// Forward declarations
class Board;
class Tile;

class Piece
{
public:
    // Constructor and destructor
    Piece(const PieceType &type, const PieceColor &c, const bool &has_moved, Tile *parent=NULL);
    virtual ~Piece();

    // Type methods
    PieceType getType() const;
    std::string getTypeString(const bool &short_notation=false) const;

    // Color methods
    PieceColor getColor() const;
    std::string getColorString() const;

    // Tile methods
    Tile* getTile();
    void setTile(Tile* tile);

    // Move methods
    virtual std::vector<Move> calculateMoves(Board *b) = 0;
    bool hasMoved() const;
    void setMoved();

protected:
    // Position of piece
    Tile* tile;

    // Type of piece
    PieceType type;

    // White or black?
    PieceColor color;

    // Has to be false for Rook and King when castling
    bool has_moved;
};

#endif // PIECE_H
