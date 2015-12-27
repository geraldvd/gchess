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

class Tile : public Field
{
public:
    Tile(const unsigned int &p);
    Tile(const unsigned int &x, const unsigned int &y);

    // Field methods
    bool tileUnderAttack(Player *p);
    std::vector<Piece_ptr> attackingPieces(Player *p);

    // Piece methods
    Piece_ptr getPiece() const;
    void setPiece(Piece_ptr p);
    void clearPiece();
    bool isOccupied() const;


private:
    // Piece
    Piece_ptr piece;
};

#endif // TILE_H
