#ifndef TYPES_H
#define TYPES_H

// Include standard libraries
#include <memory>
#include <utility>

// Forward declarations
class Piece;

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

#endif // TYPES_H

