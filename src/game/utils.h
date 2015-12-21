#ifndef UTILS_H
#define UTILS_H

// Include standard libraries
#include <memory>
#include <string>

// Forward declarations
class Piece;

// Constants
const int NUM_TILES{64};
const int NUM_TILES_X{8};
const int NUM_TILES_Y{8};

// Field class
class Field {
    int x;
    int y;
public:
    // Constructors
    Field(const int &x, const int &y);
    Field(const int &p);

    // Getters and setters
    int getX() const;
    void setX(const int &x);
    int getY() const;
    void setY(const int &y);
    int getPosition() const;
    std::string getPositionString() const;
    void setPosition(const int &p);
    void setPosition(const int &x, const int &y);
};

// Piece type
enum PieceType {KING, QUEEN, ROOK, KNIGHT, BISHOP, PAWN};

// Color type
enum PieceColor {WHITE=1, BLACK=-1};

// Check status
enum BoardStatus {BS_NORMAL, BS_CHECKWHITE, BS_CHECKBLACK, BS_CHECKMATEWHITE, BS_CHECKMATEBLACK};

// Move type
enum MoveType {MT_INVALID, MT_NORMAL, MT_PAWNJUMP, MT_CASTLING, MT_ENPASSANT, MT_PROMOTION};
enum PromotionType {PT_NONE, PT_QUEEN, PT_ROOK, PT_BISHOP, PT_KNIGHT};

// Shared pointer to piece
typedef std::shared_ptr<Piece> Piece_ptr;

#endif // UTILS_H
