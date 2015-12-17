#ifndef PIECE_H
#define PIECE_H

// Include standard libraries
#include <utility>
#include <vector>
#include <string>
#include <map>

// Include project files
#include "../field.h"
#include "../types.h"



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
    Field getPosition() const;
    std::string getPositionString() const;

    // Move methods
    virtual std::vector<Field> getMoves(const std::map<Field,Piece*> &pieces, const bool &king_check) = 0;
    virtual std::vector<Field> getPotentialMoves() = 0;
    bool fieldUnderAttack(const Field &f, const std::map<Field, Piece *> &pieces);
    bool moveOnboard(const Field &m);
    virtual bool move(const Field &m, const std::map<Field, Piece *> &pieces, const bool &king_check);

protected:
    // Type of piece
    enum PieceType type;

    // Position on the board (dependent on color)
    Field position;

    // White or black?
    enum PieceColor color;

    // Has to be false for Rook and King when castling
    bool has_moved;
};

#endif // PIECE_H
