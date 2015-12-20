// Include standard library
#include <algorithm>
#include <utility>

// Include project files
#include "king.h"
#include "board.h"

using namespace std;

King::King(const unsigned int &position, const PieceColor &c, const bool &has_moved) :
    Piece(position, c, has_moved)
{
    this->type = KING;
}

bool King::checkStatus(Board *b)
{
//    for(auto &p : b) {
//        if(p.second->fieldUnderAttack(this->getPosition(), b)) {
//            return true;
//        }
//    }
    return false;
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
        unsigned int m = this->getPosition() + d.first + 8*d.second;
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
