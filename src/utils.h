#ifndef UTILS_H
#define UTILS_H

// Include standard libraries
#include <memory>
#include <string>
#include <cstdint>

// Forward declarations
class Piece;
class Field;

// Constants
const int NUM_TILES{64};
const int NUM_TILES_X{8};
const int NUM_TILES_Y{8};

// Piece type
enum PieceType {KING=0, QUEEN=1, ROOK=2, BISHOP=3, KNIGHT=4, PAWN=5};

// Color type
enum PieceColor {WHITE=1, BLACK=-1};

// Check status
enum BoardStatus {BS_NORMAL=0, BS_CHECKWHITE=1, BS_CHECKBLACK=2, BS_CHECKMATEWHITE=3, BS_CHECKMATEBLACK=4, BS_STALEMATE=5};

// Move type
enum MoveType {MT_NONE=0, MT_NORMAL=1, MT_PAWNJUMP=2, MT_CASTLING=3, MT_ENPASSANT=4, MT_PROMOTION=5};
enum PromotionType {PT_NONE=0, PT_QUEEN=1, PT_ROOK=2, PT_BISHOP=3, PT_KNIGHT=4};
enum MoveStatus {MS_INVALID=0, MS_OK=1};

// Shared pointers
typedef std::shared_ptr<Piece> Piece_ptr;
typedef std::shared_ptr<Field> Field_ptr;

// Hash primes
const unsigned int HASH_A{54059};
const unsigned int HASH_B{76963};
const unsigned int HASH_C{86969};

// Primes
const unsigned short P_A{2};
const unsigned short P_B{3};
const unsigned short P_C{5};
const unsigned short P_D{7};
const unsigned short P_E{11};
const unsigned short P_F{13};

// BitBoard
class BitBoard {
    uint64_t bb;
public:
    bool get(const int &p)
    {
      // Checks to see if the bitboard has a value of
      // true at the bit "p" bits from the right.
      return (bb & (1 << p));
    }
    bool get(const int &x, const int &y) {
        return this->get(x+NUM_TILES_X*y);
    }
};


#endif // UTILS_H
