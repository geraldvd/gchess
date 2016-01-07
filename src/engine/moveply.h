#ifndef MOVEPLY_H
#define MOVEPLY_H

// Include standard libraries
#include <string>
#include <vector>

// Include project files
#include "../board/move.h"

class MovePly
{
public:
    MovePly(const std::string &board);

    // Getters
    std::vector<std::string> getBoardsAfterMoves() const;

private:
    std::vector<Move> moves;
    std::vector<std::string> boardsAfterMoves;
    std::vector<int> boardValues;

    // Compute board value
    int computeBoardValue(const std::string &board) const;
};

#endif // MOVEPLY_H
