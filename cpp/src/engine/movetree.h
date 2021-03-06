#ifndef MOVETREE_H
#define MOVETREE_H

// Include standard libraries
#include <string>
#include <chrono>

// Include project libraries
#include "../board/move.h"


class MoveTree
{
public:
    MoveTree();
    MoveTree(const int &numPlies, const std::string &currentBoard);

    // Getters
    unsigned int getNumPlies() const;
    double getDurationSeconds() const;
    unsigned int getNumMoves() const;


private:
    unsigned int numPlies;
    std::chrono::system_clock::time_point startTime;
    unsigned int numMoves;

    Move bestMove;
};

#endif // MOVETREE_H
