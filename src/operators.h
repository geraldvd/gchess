#ifndef OPERATORS_H
#define OPERATORS_H

// Include standard libraries
#include <ostream>

// Include project files
#include "board/tile.h"
#include "board/move.h"
#include "board/board.h"

// Forward declaration of Tile
class Tile;

// Field operators
bool operator==(const Field &f1, const Field &f2);
bool operator!=(const Field &f1, const Field &f2);
Field operator+(const Field &f1, const Field &f2);

// Move operators
bool operator==(const Move &m1, const Move &m2);
bool operator<(const Move &m1, const Move &m2);

// Board operators
std::ostream& operator<<(std::ostream& os, Board &b);
std::ostream& operator<<(std::ostream& os, Board *b);


#endif // OPERATORS_H
