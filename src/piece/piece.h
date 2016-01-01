#ifndef PIECE_H
#define PIECE_H

// Include standard libraries
#include <vector>
#include <string>

// Include project files
#include "../operators.h"

// Forward declarations
class Board;
class Tile;

class Piece
{
public:
    // Constructor and destructor
    Piece(const PieceType &type, const PieceColor &c, const bool &hasMoved=false,  Tile* tile=NULL);
    virtual ~Piece();

    // Single number representation
    short toShort() const;

    // Type methods
    PieceType getType() const;
    std::string getTypeString(const bool &shortNotation=false) const;

    // Color methods
    PieceColor getColor() const;
    std::string getColorString() const;

    // Tile methods
    Tile* getTile() const;
    void setTile(Tile* tile);

    // Move methods
    bool hasMoved() const;
    void setMoved(const bool &hasMoved);
    virtual std::vector<Move> calculateMoves(Board *b) = 0;

    // Hash for comparison
    unsigned int getHash() const;

protected:
    // Position of piece
    Tile* tile;

    // Type of piece
    PieceType type;

    // White or black?
    PieceColor color;

    // Piece moved already? (Needed for castling)
    bool moved;
};

#endif // PIECE_H
