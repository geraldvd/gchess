// Include standard libraries
#include <utility>

// Include project files
#include "linepiece.h"
#include "board/board.h"

// Specify namespaces
using namespace std;

LinePiece::LinePiece(const unsigned int &position, const PieceColor & c, const bool & hasMoved) :
    Piece(position, c, hasMoved)
{
}

std::vector<unsigned int> LinePiece::calculateMoves(Board *b)
{
    // Initialize moves
    vector<unsigned int> moves;


    // List all potentially possible moves
    vector<pair<unsigned int, unsigned int> > directions;
    if(this->getType() == QUEEN || this->getType() == BISHOP) {
        // Diagonal lines
        directions.push_back(pair<unsigned int, unsigned int>(1,1));
        directions.push_back(pair<unsigned int, unsigned int>(-1,-1));
        directions.push_back(pair<unsigned int, unsigned int>(-1,1));
        directions.push_back(pair<unsigned int, unsigned int>(1,-1));
    }
    if(this->getType() == QUEEN || this->getType() == ROOK) {
        // Straigt lines
        directions.push_back(pair<unsigned int, unsigned int>(1,0));
        directions.push_back(pair<unsigned int, unsigned int>(-1,0));
        directions.push_back(pair<unsigned int, unsigned int>(0,1));
        directions.push_back(pair<unsigned int, unsigned int>(0,-1));
    }


    // Check whether moves are allowed
    for(auto &d : directions) {
        unsigned int factor = 1;
        unsigned int m = this->getPosition() + factor*(d.first + 8*d.second);
        while(b->isOnBoard(m)) {
            if(b->getTile(m).isOccupied()) {
                if(this->getColor() != b->getTile(m).getPiece()->getColor() /* TODO && isKing() */) {
                    // Opponent piece; can be taken!
                    moves.push_back(m);
                }
                // Rest of direction vector is blocked
                break;
            } else {
                // Free place, move allowed
                moves.push_back(m);
            }

            // Next location on direction vector
            m = this->getPosition() + (++factor)*(d.first + 8*d.second);
        }
    }

    return moves;
}
