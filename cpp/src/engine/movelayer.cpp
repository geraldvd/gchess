// Include project files
#include "movelayer.h"
#include "../board/board.h"

// Specify namespaces
using namespace std;

MoveLayer::MoveLayer(const string &board, const unsigned int &tag)
{
    // Compute moves
    Board b(board);
    b.updateMoves();
    for(auto &m : b.getBoardsAfterMoves()) {
        this->moves.push_back(m.first);
        this->boardsAfterMoves.push_back(pair<string,unsigned int>(m.second, tag));
    }

}

std::vector<std::pair<string, unsigned int> > MoveLayer::getBoardsAfterMoves() const
{
    return this->boardsAfterMoves;
}

std::vector<Move> MoveLayer::getMoves() const
{
    return this->moves;
}

