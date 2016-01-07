// Include project files
#include "moveply.h"
#include "../board/board.h"

// Specify namespaces
using namespace std;

MovePly::MovePly(const string &board)
{
    // Compute moves
    Board b(board);
    b.updateMoves();
    for(auto &m : b.getBoardsAfterMoves()) {
        this->moves.push_back(m.first);
        this->boardsAfterMoves.push_back(m.second);
        this->boardValues.push_back(this->computeBoardValue(m.second));
    }

}

std::vector<string> MovePly::getBoardsAfterMoves() const
{
    return this->boardsAfterMoves;
}

int MovePly::computeBoardValue(const string & board) const
{
    Board b(board);
    int value{0};

    // Compute piece values
    for(Piece_ptr p : b.getPieces()) {
        value += p->getColor()==WHITE ? p->getValue() : -p->getValue();
    }

    // TDOO extend this!
    return value;
}

