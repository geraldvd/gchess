#include "knight.h"

using namespace std;

Knight::Knight(const Field &f, const PieceColor & c, const bool &hasMoved) :
    Piece(f, c, hasMoved)
{
    this->type = KNIGHT;
}

std::vector<Field> Knight::getMoves(const std::map<Field, Piece *> &pieces, const bool &king_check)
{
//    // Initialize moves
//    vector<Field> moves;
//    this->moves = vector<Move>();

//    // Reset check status
//    this->otherKingCheck = false;

//    // List all potentially possible moves
//    moves.push_back(this->getPosition() + Field(2,1));
//    moves.push_back(this->getPosition() + Field(2,-1));
//    moves.push_back(this->getPosition() + Field(-2,1));
//    moves.push_back(this->getPosition() + Field(-2,-1));
//    moves.push_back(this->getPosition() + Field(1,2));
//    moves.push_back(this->getPosition() + Field(1,-2));
//    moves.push_back(this->getPosition() + Field(-1,2));
//    moves.push_back(this->getPosition() + Field(-1,-2));

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
//                        } else {
//                            // King check!
//                            toAdd = false;
//                            //this->moves.push_back(Move(m, CHECK));
//                            this->otherKingCheck = true;
//                            break; // Stop looping through pieces
//                        }
//                    }
//                }
//            }
//            // Place is free, move!
//            if(toAdd) {
//                this->moves.push_back(Move(m, NORMAL));
//            }
//        }
    //    }
}

std::vector<Field> Knight::getPotentialMoves()
{
    // Initialize moves
    vector<Field> moves;

    // List all potentially possible moves
    moves.push_back(this->getPosition() + Field(2,1));
    moves.push_back(this->getPosition() + Field(2,-1));
    moves.push_back(this->getPosition() + Field(-2,1));
    moves.push_back(this->getPosition() + Field(-2,-1));
    moves.push_back(this->getPosition() + Field(1,2));
    moves.push_back(this->getPosition() + Field(1,-2));
    moves.push_back(this->getPosition() + Field(-1,2));
    moves.push_back(this->getPosition() + Field(-1,-2));

    // Check whether moves are on board
    for(vector<Field>::iterator it = moves.begin(); it != moves.end(); it++) {
        if(!this->moveOnboard(*it)) {
            moves.erase(it);
        }
    }

    return moves;
}


