#include "king.h"
#include <algorithm>
#include <cstdlib>

using namespace std;

King::King(const Field &f, const PieceColor & c, const bool & has_moved) :
    Piece(f, c, has_moved)
{
    this->type = KING;
}

bool King::move(const Field &m, const map<Field,Piece*> &pieces, const bool &king_check)
{
    vector<Field> moves = this->getMoves(pieces, king_check);

    if(find(moves.begin(), moves.end(), m) != moves.end()) {
//        // Move is in list of possible moves, check castling
//        if(abs(m.getX()-this->position.getX()) > 1) {
//            // Castling, check rook!
//            for(auto &r : this->castlingRooks) {
//                if(abs(m.first.first-r->getPosition().first) == 1 && (m.first.second-r->getPosition().second) == 0) {
//                    // This is the rook!
//                    r->move(m + Field((m.first.first-r->getPosition().first),0));
//                }
//            }
//            this->moveType = CASTLING;
//        } else {
//            this->moveType = NORMAL;
//        }
        this->position = m;
        this->has_moved = true;
        return true;
    } else {
        // Move is not allowed!
        return false;
    }
}

bool King::checkStatus(const std::map<Field, Piece *> &pieces)
{
    for(auto &p : pieces) {
        if(p.second->fieldUnderAttack(this->getPosition(), pieces)) {
            return true;
        }
    }
    return false;
}

vector<Field> King::getMoves(const std::map<Field, Piece *> &pieces, const bool &king_check)
{
    // Initialize moves
    vector<Field> moves = this->getPotentialMoves();


//    // Check whether moves are allowed
//    for(auto &m : moves) {
//        if(this->moveOnboard(m)) {
//            bool toAdd{true};
//            for(auto &p : pieces) {
//                if(m == p->getPosition()) {
//                    if(p->getColor() == this->getColor()) {
//                        // Same color: don't add
//                        toAdd = false;
//                        break; // Stop looping through pieces
//                    } else {
//                        // Opponent check move
//                        if(p->getType() != KING) {
//                            // Piece can be taken!
//                            this->moves.push_back(Move(m, NORMAL));
//                            toAdd = false;
//                            break; // Stop looping through pieces
//                        }
//                    }
//                }
//            }
//            // Place is free, check whether king is next to that place!
//            if(toAdd) {
//                this->moves.push_back(Move(m, NORMAL));
//            }
//        }
//    }

//    // Check whether other king is approached
//    vector<Move> moves2 = this->moves;
//    this->moves = vector<Move>();
//    // Calculate permutes
//    vector<Field> permutes;
//    permutes.push_back(Field(1,0));
//    permutes.push_back(Field(-1,0));
//    permutes.push_back(Field(0,1));
//    permutes.push_back(Field(0,-1));
//    permutes.push_back(Field(1,1));
//    permutes.push_back(Field(-1,-1));
//    permutes.push_back(Field(-1,1));
//    permutes.push_back(Field(1,-1));
//    // Loop through moves
//    for(auto &m : moves2) {
//        bool toAdd{true};
//        for(auto &per : permutes) {
//            Field m2 = m.first + per;
//            for(auto &p : pieces) {
//                if(p->getColor() != this->getColor() && p->getType() == KING && m2 == p->getPosition()) {
//                    // Move not allowed, king to close!
//                    toAdd = false;
//                }
//            }
//        }
//        if(toAdd) {
//            this->moves.push_back(m);
//        }
//    }

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
//                for(int i=a+1; i<b; i++) {
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
}

vector<Field> King::getPotentialMoves()
{
    // Initialize moves
    vector<Field> moves;

    // List all potentially possible moves
    moves.push_back(this->getPosition() + Field(1,0));
    moves.push_back(this->getPosition() + Field(-1,0));
    moves.push_back(this->getPosition() + Field(0,1));
    moves.push_back(this->getPosition() + Field(0,-1));
    moves.push_back(this->getPosition() + Field(1,1));
    moves.push_back(this->getPosition() + Field(-1,-1));
    moves.push_back(this->getPosition() + Field(-1,1));
    moves.push_back(this->getPosition() + Field(1,-1));

    // Check whether moves are on board
    for(vector<Field>::iterator it = moves.begin(); it != moves.end(); it++) {
        if(!this->moveOnboard(*it)) {
            moves.erase(it);
        }
    }

    return moves;
}
