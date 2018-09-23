// Include standard libraries
#include <utility>
#include <iostream>

// Include project files
#include "knight.h"
#include "../operators.h"
#include "../board/board.h"
#include "../board/move.h"

// Specify namespaces
using namespace std;

Knight::Knight(const PieceColor & c, const bool &hasMoved, Tile *parent) :
    Piece(KNIGHT, c, 3, hasMoved, false, parent)
{
}

std::vector<Move> Knight::calculateMoves(Board *b)
{
    // Initialize moves
    vector<Move> moves;


    // List all potentially possible moves
    vector<pair<int, int> > displacements = {
        pair<int, int>(2,1),
        pair<int, int>(2,-1),
        pair<int, int>(-2,1),
        pair<int, int>(-2,-1),
        pair<int, int>(1,2),
        pair<int, int>(1,-2),
        pair<int, int>(-1,2),
        pair<int, int>(-1,-2)
    };

    // Check whether moves are allowed
    for(auto &d : displacements) {
        int mx = this->getTile()->getX() + d.first;
        int my = this->getTile()->getY() + d.second;
        if(b->isOnBoard(mx, my)) {
            if(b->getTile(mx, my)->isOccupied()) {
                if(this->getColor() != b->getTile(mx, my)->getPiece()->getColor() /* TODO && isKing() */) {
                    // Opponent piece; can be taken!
                    moves.push_back(Move(mx, my, this->getTile()->getPiece(), MT_NORMAL));
                }
            } else {
                // Free place, move allowed
                moves.push_back(Move(mx, my, this->getTile()->getPiece(), MT_NORMAL));
            }
        }
    }

    return moves;
}


