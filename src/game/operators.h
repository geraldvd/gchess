#ifndef OPERATORS_H
#define OPERATOR_H

// Include project files
#include "board/tile.h"
#include "board/move.h"

// Forward declaration of Tile
class Tile;

// Tile operators
Tile operator+(const Tile &t1, const Tile &t2);
bool operator==(const Tile &t1, const Tile &t2);
bool operator<(const Tile &t1, const Tile &t2);
bool operator>(const Tile &t1, const Tile &t2);

// Move operators
Move operator+(const Move &m, const unsigned int &i);
Move operator+(const unsigned int &i, const Move &m);

#endif // OPERATORS_H
