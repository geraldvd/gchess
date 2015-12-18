#include "board.h"

using namespace std;

Board::Board() :
    board_status(BS_NORMAL)
{
    unsigned int i{0};
    while(i < Board::NUM_TILES) {
        this->tiles.push_back(i++);
    }
}

Tile Board::getTile(const unsigned int &i) const
{
        return this->tiles.at(i);
}
