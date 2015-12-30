#ifndef TILE_H
#define TILE_H

// Include standard libraries
#include <utility>
#include <string>
#include <memory>
#include <vector>

// Include project files
#include "../utils.h"
#include "field.h"

// Forward declarations
class Piece;
class Board;
class Player;
class Move;

class Tile : public Field
{
public:
    Tile();
    Tile(const unsigned int &x, const unsigned int &y);

    // Field methods
    std::vector<Piece_ptr> attackingPieces(Board * b, const PieceColor & attackingColor);

    // Piece methods
    Piece_ptr getPiece() const;
    void setPiece(const Piece_ptr &p);
    void clearPiece();
    bool isOccupied() const;


private:
    // Piece
    Piece_ptr piece;
};

#endif // TILE_H
