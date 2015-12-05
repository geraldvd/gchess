#include "knight.h"

using namespace std;

Knight::Knight(const int & x, const int & y, const Color & c, const bool &hasMoved) :
    Piece(x, y, c, hasMoved)
{
    this->type = "Knight";
}

void Knight::findMoves(const std::vector<Piece*> & pieces)
{
    // Initialize moves
    vector<Field> moves;
    this->moves = vector<Field>();

    // List all potentially possible moves
    moves.push_back(this->getPosition() + Field(2,1));
    moves.push_back(this->getPosition() + Field(2,-1));
    moves.push_back(this->getPosition() + Field(-2,1));
    moves.push_back(this->getPosition() + Field(-2,-1));
    moves.push_back(this->getPosition() + Field(1,2));
    moves.push_back(this->getPosition() + Field(1,-2));
    moves.push_back(this->getPosition() + Field(-1,2));
    moves.push_back(this->getPosition() + Field(-1,-2));

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
}

