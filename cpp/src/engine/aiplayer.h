#ifndef AIPLAYER_H
#define AIPLAYER_H

// Include standard libraries
#include <thread>
#include <string>

// Include project files
#include "movetree.h"
#include "../utils.h"


class AiPlayer
{
public:
    AiPlayer();

    // Evaluate board and find best move
    void eval(const std::string &board);
    void evalThread();


private:
    bool evalDone;
    std::string currentBoard;
};

#endif // AIPLAYER_H
