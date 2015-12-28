// Include standard library
#include <algorithm>
#include <utility>

// Include project files
#include "king.h"
#include "board.h"

using namespace std;

King::King(const PieceColor &c, const bool &has_moved, Tile *tile) :
    Piece(KING, c, has_moved, tile)
{
}

std::vector<Move> King::calculateMoves(Board *b)
{
    // Initialize moves
    vector<Move> moves;


    // List all potentially possible moves
    vector<pair<unsigned int, unsigned int> > displacements = {
        pair<unsigned int, unsigned int>(1,0),
        pair<unsigned int, unsigned int>(-1,0),
        pair<unsigned int, unsigned int>(0,1),
        pair<unsigned int, unsigned int>(0,-1),
        pair<unsigned int, unsigned int>(1,1),
        pair<unsigned int, unsigned int>(1,-1),
        pair<unsigned int, unsigned int>(-1,1),
        pair<unsigned int, unsigned int>(-1,-1)
    };

    // Check whether moves are allowed
    for(auto &d : displacements) {
        int mx = this->getTile()->getX() + d.first;
        int my = this->getTile()->getY() + d.second;
        if(b->isOnBoard(mx, my)) {
            // Check whether opponent king is too close (note: displacements vector can be used)
            bool kingTooClose{false};
            for(auto &k : displacements) {
                int kingPositionX = mx + k.first;
                int kingPositionY = my + k.second;
                if(b->isOnBoard(kingPositionX, kingPositionY) && b->getTile(kingPositionX, kingPositionY)->isOccupied()
                        && b->getTile(kingPositionX, kingPositionY)->getPiece()->getColor() != this->getColor()
                        && b->getTile(kingPositionX, kingPositionY)->getPiece()->getType() == KING) {
                    kingTooClose = true;
                }
            }

            if(!kingTooClose) {
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
    }

    // Check castling
    if(!this->moved && this->getTile()->getX() == 4) {
        if((this->getColor() == WHITE && this->getTile()->getY() == 0) ||
                (this->getColor() == BLACK && this->getTile()->getY() == 7)) {
            // Check rooks to the right
            if(!b->getTile(this->getTile()->getX()+1, this->getTile()->getY())->isOccupied() &&     // Field next to king must be empty
                    !b->getTile(this->getTile()->getX()+2, this->getTile()->getY())->isOccupied() && // Field next to rook must be empty
                    b->getTile(this->getTile()->getX()+3, this->getTile()->getY())->isOccupied() && // Is there a piece in the corner?
                    b->getTile(this->getTile()->getX()+3, this->getTile()->getY())->getPiece()->getType() == ROOK && // Is the piece a rook?
                    b->getTile(this->getTile()->getX()+3, this->getTile()->getY())->getPiece()->getColor() == this->getColor() && // Is the color the same?
                    !b->getTile(this->getTile()->getX()+3, this->getTile()->getY())->getPiece()->hasMoved()) { // Did the rook move already?
                Move m(this->getTile()->getX()+2, this->getTile()->getY(), this->getTile()->getPiece(), MT_CASTLING);
                m.setCastlingRookPosition(b->getTile(this->getTile()->getX()+3, this->getTile()->getY())->getPosition());
                moves.push_back(m);
            }

            // Check rooks to the left
            if(!b->getTile(this->getTile()->getX()-1, this->getTile()->getY())->isOccupied() &&     // Field next to king must be empty
                    !b->getTile(this->getTile()->getX()-2, this->getTile()->getY())->isOccupied() && // Middle field must be empty
                    !b->getTile(this->getTile()->getX()-3, this->getTile()->getY())->isOccupied() && // Field next to rook must be empty
                    b->getTile(this->getTile()->getX()-4, this->getTile()->getY())->isOccupied() && // Is there a piece in the corner?
                    b->getTile(this->getTile()->getX()-4, this->getTile()->getY())->getPiece()->getType() == ROOK && // Is the piece a rook?
                    b->getTile(this->getTile()->getX()-4, this->getTile()->getY())->getPiece()->getColor() == this->getColor() && // Is the color the same?
                    !b->getTile(this->getTile()->getX()-4, this->getTile()->getY())->getPiece()->hasMoved()) { // Did the rook move already?
                Move m(this->getTile()->getX()-2, this->getTile()->getY(), this->getTile()->getPiece(), MT_CASTLING);
                m.setCastlingRookPosition(b->getTile(this->getTile()->getX()-4, this->getTile()->getY())->getPosition());
                moves.push_back(m);
            }
        }
    }

    return moves;
}
