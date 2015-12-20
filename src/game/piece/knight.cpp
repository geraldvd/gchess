// Include standard libraries
#include <utility>

// Include project files
#include "knight.h"
#include "operators.h"
#include "board/board.h"
#include "board/move.h"

// Specify namespaces
using namespace std;

Knight::Knight(const unsigned int &position, const PieceColor & c, const bool &hasMoved) :
    Piece(position, c, hasMoved)
{
    this->type = KNIGHT;
}

std::vector<Move> Knight::calculateMoves(Board *b)
{
    // Initialize moves
    vector<Move> moves;


    // List all potentially possible moves
    vector<pair<unsigned int, unsigned int> > displacements = {
        pair<unsigned int, unsigned int>(2,1),
        pair<unsigned int, unsigned int>(2,-1),
        pair<unsigned int, unsigned int>(-2,1),
        pair<unsigned int, unsigned int>(-2,-1),
        pair<unsigned int, unsigned int>(1,2),
        pair<unsigned int, unsigned int>(1,-2),
        pair<unsigned int, unsigned int>(-1,2),
        pair<unsigned int, unsigned int>(-1,-2)
    };

    // Check whether moves are allowed
    for(auto &d : displacements) {
        unsigned int m = this->getPosition() + d.first + 8*d.second;
        if(b->isOnBoard(m)) {
            if(b->getTile(m)->isOccupied()) {
                if(this->getColor() != b->getTile(m)->getPiece()->getColor() /* TODO && isKing() */) {
                    // Opponent piece; can be taken!
                    moves.push_back(Move(m, MT_NORMAL));
                }
            } else {
                // Free place, move allowed
                moves.push_back(Move(m, MT_NORMAL));
            }
        }
    }

    return moves;
}


