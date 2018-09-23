#ifndef MOVELAYER_H
#define MOVELAYER_H

// Include standard libraries
#include <string>
#include <vector>
#include <utility>

// Include project files
#include "../board/move.h"

class MoveLayer
{
public:
    MoveLayer(const std::string &board, const unsigned int &tag);

    // Getters
    std::vector<std::pair<std::string,unsigned int> > getBoardsAfterMoves() const;
    std::vector<Move> getMoves() const;

private:
    std::vector<Move> moves;
    std::vector<std::pair<std::string,unsigned int> > boardsAfterMoves;
};

#endif // MOVELAYER_H
