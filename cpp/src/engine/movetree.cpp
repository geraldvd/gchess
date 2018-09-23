// Include standard libraries
#include <vector>
#include <utility>

// Include project files
#include "movetree.h"
#include "movelayer.h"
#include "../board/board.h"

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
    // Compute moves to choose from
    MoveLayer firstLayer(currentBoard, 0);
    vector<Move> movesToChooseFrom = firstLayer.getMoves();

    // Initialize boards
    vector<pair<string,unsigned int> > currentBoards = firstLayer.getBoardsAfterMoves();
    vector<pair<string,unsigned int> > resultingBoards;

    // Give correct "tags"; i.e., which first moves belongs to certain moves
    unsigned int counter{0};
    for(auto &i : currentBoards) {
        i.second = counter++;
    }

    // Calculate all plies
    for(int i=0; i<numPlies; i++) {
        // Loop through boards
        for(auto &b : currentBoards) {
            MoveLayer layer(b.first, b.second);
            vector<pair<string,unsigned int> > boardsAfterMoves = layer.getBoardsAfterMoves();
            resultingBoards.insert(resultingBoards.end(), boardsAfterMoves.begin(), boardsAfterMoves.end());
        }

        // Set numbers
        this->numPlies = i + 1;
        this->numMoves = resultingBoards.size();

        // Reset boards
        currentBoards = resultingBoards;
        resultingBoards.clear();
    }

    // Find best opponent move (for min-max algorithm)
    vector<pair<string,unsigned int> > opponentBoards;
    int bestValue{0};
    string bestBoard;
    unsigned int currentIndex{0};
    for(auto &r : currentBoards) {
        // Compute board value
        Board currentBoard = Board(r.first);
        int boardValue = currentBoard.computeBoardValue();

        // Update index
        if(currentIndex != r.second) {
            // Insert best opponent move (of previous index)
            opponentBoards.push_back(pair<string,unsigned int>(bestBoard, currentIndex));

            // Reset bestvalue
            currentIndex = r.second;
            bestValue = 0;
        }

        // Evaluate whether move is best
        if((currentBoard.getActivePlayer() == WHITE && boardValue>bestValue) ||
           (currentBoard.getActivePlayer() == BLACK && boardValue<bestValue)) {
            bestValue = boardValue;
            bestBoard = r.first;
        }
    }
    opponentBoards.push_back(pair<string,unsigned int>(bestBoard, currentIndex));

    // Find best move
    bestValue = 0;
    bestBoard = string();
    unsigned int correspondingMove{0};

    for(auto &b : opponentBoards) {
        // Compute board value
        Board currentBoard = Board(b.first);
        int boardValue = currentBoard.computeBoardValue();

        // Evaluate whether move is best
        if((currentBoard.getActivePlayer() == WHITE && boardValue>bestValue) ||
           (currentBoard.getActivePlayer() == BLACK && boardValue<bestValue)) {
            bestValue = boardValue;
            bestBoard = b.first;
            correspondingMove = b.second;
        }
    }

    this->bestMove = movesToChooseFrom.at(correspondingMove);
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

