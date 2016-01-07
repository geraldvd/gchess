// Include standard libraries
#include <utility>

// Include project files
#include "linepiece.h"
#include "../board/board.h"

// Specify namespaces
using namespace std;

LinePiece::LinePiece(const PieceType &type, const PieceColor &c, const int &v, const bool &hasMoved, Tile *parent) :
    Piece(type, c, v, hasMoved, false, parent)
{
}

std::vector<Move> LinePiece::calculateMoves(Board *b)
{
    // Initialize moves
    vector<Move> moves;


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
        int mx = this->getTile()->getX() + factor*d.first;
        int my = this->getTile()->getY() + factor*d.second;
        while(b->isOnBoard(mx, my)) {
            if(b->getTile(mx, my)->isOccupied()) {
                if(this->getColor() != b->getTile(mx, my)->getPiece()->getColor() /* TODO && isKing() */) {
                    // Opponent piece; can be taken!
                    moves.push_back(Move(mx, my, this->getTile()->getPiece(), MT_NORMAL));
                }
                // Rest of direction vector is blocked
                break;
            } else {
                // Free place, move allowed
                moves.push_back(Move(mx, my, this->getTile()->getPiece(), MT_NORMAL));
            }

            // Next location on direction vector
            mx = this->getTile()->getX() + (++factor)*d.first;
            my = this->getTile()->getY() + factor*d.second;
        }
    }

    return moves;
}
