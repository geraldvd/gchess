// Include standard library
#include <algorithm>
#include <utility>

// Include project files
#include "king.h"
#include "board.h"

using namespace std;

King::King(const PieceColor &c, const bool &has_moved, Tile *parent) :
    Piece(c, has_moved, parent)
{
    this->type = KING;
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
        unsigned int m = this->getTile()->getPosition() + d.first + 8*d.second;
        if(b->isOnBoard(m)) {
            // Check whether opponent king is too close (note: displacements vector can be used)
            bool kingTooClose{false};
            for(auto &k : displacements) {
                unsigned int kingPosition = m + k.first + 8*k.second;
                if(b->isOnBoard(kingPosition) && b->getTile(kingPosition)->isOccupied()
                        && b->getTile(kingPosition)->getPiece()->getColor() != this->getColor()
                        && b->getTile(kingPosition)->getPiece()->getType() == KING) {
                    kingTooClose = true;
                }
            }

            if(!kingTooClose) {
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
    }

    // Check castling
    if(!this->has_moved && this->getTile()->getX() == 4) {
        if((this->getColor() == WHITE && this->getTile()->getY() == 0) ||
                (this->getColor() == BLACK && this->getTile()->getY() == 7)) {
            // Check rooks to the right
            if(!b->getTile(this->getTile()->getX()+1, this->getTile()->getY())->isOccupied() &&     // Field next to king must be empty
                    !b->getTile(this->getTile()->getX()+2, this->getTile()->getY())->isOccupied() && // Field next to rook must be empty
                    b->getTile(this->getTile()->getX()+3, this->getTile()->getY())->isOccupied() && // Is there a piece in the corner?
                    b->getTile(this->getTile()->getX()+3, this->getTile()->getY())->getPiece()->getType() == ROOK && // Is the piece a rook?
                    b->getTile(this->getTile()->getX()+3, this->getTile()->getY())->getPiece()->getColor() == this->getColor() && // Is the color the same?
                    !b->getTile(this->getTile()->getX()+3, this->getTile()->getY())->getPiece()->hasMoved()) { // Did the rook move already?
                moves.push_back(Move(this->getTile()->getX()+2, this->getTile()->getY(), MT_CASTLING));
            }

            // Check rooks to the left
            if(!b->getTile(this->getTile()->getX()-1, this->getTile()->getY())->isOccupied() &&     // Field next to king must be empty
                    !b->getTile(this->getTile()->getX()-2, this->getTile()->getY())->isOccupied() && // Middle field must be empty
                    !b->getTile(this->getTile()->getX()-3, this->getTile()->getY())->isOccupied() && // Field next to rook must be empty
                    b->getTile(this->getTile()->getX()-4, this->getTile()->getY())->isOccupied() && // Is there a piece in the corner?
                    b->getTile(this->getTile()->getX()-4, this->getTile()->getY())->getPiece()->getType() == ROOK && // Is the piece a rook?
                    b->getTile(this->getTile()->getX()-4, this->getTile()->getY())->getPiece()->getColor() == this->getColor() && // Is the color the same?
                    !b->getTile(this->getTile()->getX()-4, this->getTile()->getY())->getPiece()->hasMoved()) { // Did the rook move already?
                moves.push_back(Move(this->getTile()->getX()-3, this->getTile()->getY(), MT_CASTLING));
            }
        }
    }

    return moves;

// TODO castling

//    // Check castling
//    this->castlingRooks = vector<Piece*>();
//    if(!this->hasMoved) {
//        for(auto &p : pieces) {
//            if(p->getType() == ROOK && p->getColor() == this->getColor() && !p->hasMoved) {
//                bool castlingAllowed{true};
//                // Check whether fields between King and Rook are empty
//                int a{0}, b{0};
//                if(p->getPosition().first > this->getPosition().first) {
//                    // Start from King position
//                    a = this->getPosition().first;
//                    b = p->getPosition().first;
//                } else {
//                    // Start from Rook position
//                    a = p->getPosition().first;
//                    b = this->getPosition().first;
//                }
//                for(int i=a+1; i<b; i++) of{
//                    for(auto &p2 : pieces) {
//                        if(this->getColor() == WHITE) {
//                            if(p2->getPosition() == Field(i,0)) {
//                                // Castling not allowed!
//                                castlingAllowed = false;
//                            }
//                        } else {
//                            if(p2->getPosition() == Field(i,7)) {
//                                // Castling not allowed!
//                                castlingAllowed = false;
//                            }
//                        }
//                    }
//                }
//                // TODO: check whether fields between King and Rook are in check state!
//                if(castlingAllowed) {
//                    if(this->getColor() == WHITE) {
//                        if(this->moveOnboard(Field(p->getPosition().first+1, 0))) {
//                            this->moves.push_back(Move(Field(p->getPosition().first+1, 0), CASTLING));
//                        } else {
//                            this->moves.push_back(Move(Field(p->getPosition().first-1, 0), CASTLING));
//                        }
//                    } else {
//                        if(this->moveOnboard(Field(p->getPosition().first+1, 7))) {
//                            this->moves.push_back(Move(Field(p->getPosition().first+1, 7), CASTLING));
//                        } else {
//                            this->moves.push_back(Move(Field(p->getPosition().first-1, 7), CASTLING));
//                        }
//                    }
//                    this->castlingRooks.push_back(p);
//                }
//            }
//        }
//        }
    return moves;
}
