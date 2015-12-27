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

// Piece type
enum PieceType {KING, QUEEN, ROOK, KNIGHT, BISHOP, PAWN};

// Color type
enum PieceColor {WHITE=1, BLACK=-1};

// Check status
enum BoardStatus {BS_NORMAL, BS_CHECKWHITE, BS_CHECKBLACK, BS_CHECKMATEWHITE, BS_CHECKMATEBLACK, BS_STALEMATE};

// Move type
enum MoveType {MT_NONE=0, MT_NORMAL=1, MT_PAWNJUMP=2, MT_CASTLING=3, MT_ENPASSANT=4, MT_PROMOTION=5};
enum PromotionType {PT_NONE=0, PT_QUEEN=1, PT_ROOK=2, PT_BISHOP=3, PT_KNIGHT=4};
enum MoveStatus {MS_INVALID=0, MS_OK=1, MS_PROMOTION=2};

// Shared pointer to piece
typedef std::shared_ptr<Piece> Piece_ptr;

// Extra functions


#endif // UTILS_H
