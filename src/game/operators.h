#ifndef OPERATORS_H
#define OPERATOR_H

// Include standard libraries
#include <ostream>

// Include project files
#include "board/tile.h"
#include "board/move.h"
#include "board/board.h"

// Forward declaration of Tile
class Tile;

// Tile operators TODO: must be field operations
Tile operator+(const Tile &t1, const Tile &t2);
bool operator==(const Tile &t1, const Tile &t2);
bool operator<(const Tile &t1, const Tile &t2);
bool operator>(const Tile &t1, const Tile &t2);

// Move operators - TODO: must be field operations
Move operator+(const Move &m, const unsigned int &i);
Move operator+(const unsigned int &i, const Move &m);

// Board operators
std::ostream& operator<<(std::ostream& os, Board *b);


#endif // OPERATORS_H
