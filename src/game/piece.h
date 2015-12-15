#ifndef PIECE_H
#define PIECE_H

// Include standard libraries
#include <utility>
#include <vector>
#include <string>
#include <map>

// Include project files
#include "field.h"
#include "types.h"



class Piece
{
public:
    // Constructor and destructor
    Piece(const Field &f, const enum PieceColor &c, const bool &has_moved);
    virtual ~Piece();

    // Getters
    enum PieceType getType() const;
    enum PieceColor getColor() const;
    std::string getColorString() const;
    std::vector<Field> getMoves() const;
    Field getPosition() const;
    std::string getPositionString() const;

    // Move methods
    virtual void findMoves(const std::map<Field,Piece*> &pieces) = 0;
//    bool moveOnboard(const Field &m);
    virtual bool move(const Field &m);

protected:
    // Type of piece
    enum PieceType type;

    // Position on the board (dependent on color)
    Field position;

    // White or black?
    enum PieceColor color;

    // Possible moves; populated by findMoves()
    std::vector<Field> moves;

    // Has to be false for Rook and King when castling
    bool has_moved;
};

#endif // PIECE_H
