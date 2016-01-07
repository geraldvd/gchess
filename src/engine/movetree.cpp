// Include standard libraries
#include <vector>

// Include project files
#include "movetree.h"
#include "moveply.h"
#include "../board/move.h"

// Specify namespaces
using namespace std;

MoveTree::MoveTree()
{

}

MoveTree::MoveTree(const int &numPlies, const string &currentBoard) :
    numPlies(0),
    startTime(chrono::system_clock::now()),
    numMoves(0)
{
    vector<string> currentBoards = {currentBoard};
    vector<string> resultingBoards;

    for(int i=0; i<numPlies; i++) {
        // Loop through boards
        for(auto &b : currentBoards) {
            MovePly ply(b);
            //resultingBoards.insert(resultingBoards.end(), ply.getBoardsAfterMoves().begin(), ply.getBoardsAfterMoves().end());
            vector<string> boardsAfterMoves = ply.getBoardsAfterMoves();
            resultingBoards.insert(resultingBoards.end(), boardsAfterMoves.begin(), boardsAfterMoves.end());
        }

        // Set numbers
        this->numPlies = i + 1;
        this->numMoves = resultingBoards.size();

        // Reset boards
        currentBoards = resultingBoards;
        resultingBoards.clear();

    }

}

unsigned int MoveTree::getNumPlies() const
{
    return this->numPlies;
}

double MoveTree::getDurationSeconds() const
{
    chrono::duration<double> duration = chrono::system_clock::now() - this->startTime;
    return duration.count();
}

unsigned int MoveTree::getNumMoves() const
{
    return this->numMoves;
}

