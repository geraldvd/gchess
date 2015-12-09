#include "king.h"

using namespace std;

King::King(const int & x, const int & y, const PieceColor & c, const bool & hasMoved) :
    Piece(x, y, c, hasMoved)
{
    this->type = "King";
}

void King::findMoves(const std::vector<Piece*> & pieces)
{
    // Initialize moves
    vector<Field> moves;
    this->moves = vector<Field>();

    // List all potentially possible moves
    moves.push_back(this->getPosition() + Field(1,0));
    moves.push_back(this->getPosition() + Field(-1,0));
    moves.push_back(this->getPosition() + Field(0,1));
    moves.push_back(this->getPosition() + Field(0,-1));
    moves.push_back(this->getPosition() + Field(1,1));
    moves.push_back(this->getPosition() + Field(-1,-1));
    moves.push_back(this->getPosition() + Field(-1,1));
    moves.push_back(this->getPosition() + Field(1,-1));

    // Check whether moves are allowed
    for(auto &m : moves) {
        if(this->moveOnboard(m)) {
            bool toAdd{true};
            for(auto &p : pieces) {
                if(m == p->getPosition()) {
                    if(p->getColor() == this->getColor()) {
                        // Same color: don't add
                        toAdd = false;
                        break; // Stop looping through pieces
                    } else {
                        // Opponent check move
                        if(p->getType() != "King") {
                            // Piece can be taken!
                            this->moves.push_back(m);
                            toAdd = false;
                            break; // Stop looping through pieces
                        }
                    }
                }
            }
            // Place is free, move!
            if(toAdd) {
                this->moves.push_back(m);
            }
        }
    }

    // Check castling
    if(!this->hasMoved) {
        for(auto &p : pieces) {
            if(p->getType() == "Rook" && p->getColor() == this->getColor() && !p->hasMoved) {
                bool castlingAllowed{true};
                // Check whether fields between King and Rook are empty
                int a{0}, b{0};
                if(p->getPosition().first > this->getPosition().first) {
                    // Start from King position
                    a = this->getPosition().first;
                    b = p->getPosition().first;
                } else {
                    // Start from Rook position
                    a = p->getPosition().first;
                    b = this->getPosition().first;
                }
                for(int i=a+1; i<b; i++) {
                    for(auto &p2 : pieces) {
                        if(this->getColor() == WHITE) {
                            if(p2->getPosition() == Field(i,0)) {
                                // Castling not allowed!
                                castlingAllowed = false;
                            }
                        } else {
                            if(p2->getPosition() == Field(i,7)) {
                                // Castling not allowed!
                                castlingAllowed = false;
                            }
                        }
                    }
                }
                // TODO: check whether fields between King and Rook are in check state!
                if(castlingAllowed) {
                    if(this->getColor() == WHITE) {
                        if(this->moveOnboard(Field(p->getPosition().first+1, 0))) {
                            this->moves.push_back(Field(p->getPosition().first+1, 0));
                        } else {
                            this->moves.push_back(Field(p->getPosition().first-1, 0));
                        }
                    } else {
                        if(this->moveOnboard(Field(p->getPosition().first+1, 7))) {
                            this->moves.push_back(Field(p->getPosition().first+1, 7));
                        } else {
                            this->moves.push_back(Field(p->getPosition().first-1, 7));
                        }
                    }
                }
            }
        }
    }
}

