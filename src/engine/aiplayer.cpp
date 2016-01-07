// Include project files
#include "aiplayer.h"

// Specify namespaces
using namespace std;

AiPlayer::AiPlayer() :
    evalDone(true)
{

}

void AiPlayer::eval(const string &board)
{
    if(evalDone) {
        this->evalDone = false;
        this->currentBoard = board;
        thread aiThread(&AiPlayer::evalThread, AiPlayer());
    }
}

void AiPlayer::evalThread()
{
    MoveTree tree(2, this->currentBoard);

    this->evalDone = true;
}

