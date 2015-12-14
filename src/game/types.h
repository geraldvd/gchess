#ifndef TYPES_H
#define TYPES_H

// Include standard libraries
#include <utility>

// Piece type
enum PieceType {KING, QUEEN, ROOK, KNIGHT, BISHOP, PAWN};

// Color type
enum PieceColor {WHITE=1, BLACK=-1};

// Move type
enum MoveType {NONE, INVALID, NORMAL, CASTLING, ENPASSANT, PROMOTION_QUEEN, PROMOTION_ROOK, PROMOTION_KNIGHT, PROMOTION_BISHOP};

#endif // TYPES_H

