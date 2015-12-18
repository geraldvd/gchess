#include "linepiece.h"

#include <utility>

using namespace std;

LinePiece::LinePiece(const Field &f, const PieceColor & c, const bool & hasMoved) :
    Piece(f, c, hasMoved)
{
}

vector<Field> LinePiece::getMoves(const std::map<Field, Piece *> &pieces, const bool &king_check)
{
//    // TODO

//    // Initialize moves
//    vector<Field> moves;

//    // Store whether line is blocked, and whether move is still valid
//    vector<pair<Field,bool> > directions;
//    if(this->getType() == QUEEN || this->getType() == BISHOP) {
//        // Diagonal lines
//        directions.push_back(pair<Field,bool>(Field(1,1), true));
//        directions.push_back(pair<Field,bool>(Field(-1,-1), true));
//        directions.push_back(pair<Field,bool>(Field(-1,1), true));
//        directions.push_back(pair<Field,bool>(Field(1,-1), true));
//    }
//    if(this->getType() == QUEEN || this->getType() == ROOK) {
//        // Straigt lines
//        directions.push_back(pair<Field,bool>(Field(1,0), true));
//        directions.push_back(pair<Field,bool>(Field(-1,0), true));
//        directions.push_back(pair<Field,bool>(Field(0,1), true));
//        directions.push_back(pair<Field,bool>(Field(0,-1), true));
//    }

//    // Initialize possible moves
//    for(int i=1; i<8; i++) {
//        for(auto &d : directions) {
//            // Check whether line was already occupied
//            if(d.second) {
//                Field m = this->getPosition() + Field(d.first.first*i, d.first.second*i);

//                if(this->moveOnboard(m)) {
//                    for(auto &p : pieces) {
//                        if(m == p->getPosition()) {
//                            if(p->getColor() == this->getColor()) {
//                                // Same color: don't add and don't continue with line
//                                d.second = false;
//                                break; // Stop looping through pieces
//                            } else {
//                                // Opponent check move!
//                                if(p->getType() != KING) {
//                                    // Piece can be taken! Don't continue; piece cannot be passed
//                                    d.second = false;
//                                    moves.push_back(Move(m, NORMAL));
//                                    break; // Stop looping through pieces
//                                } else {
//                                    // King check! Move cannot be made!
//                                    d.second = false;
//                                    this->otherKingCheck = true;
//                                    //moves.push_back(Move(m, CHECK));
//                                    break; // Stop looping through pieces
//                                }
//                            }
//                        }
//                    }
//                    // Free place, so allowed
//                    if(d.second) {
//                        moves.push_back(Move(m, NORMAL));
//                    }
//                } else {
//                    // Next positions should not be tried
//                    d.second = false;
//                }
//            }
//        }
//    }

//    // Check whether moves are still on board
    //    this->moves = moves;
    return vector<Field>();
}

std::vector<Field> LinePiece::getPotentialMoves()
{
    vector<Field> moves;

    // Store whether line is blocked, and whether move is still valid
    vector<Field> directions;
    if(this->getType() == QUEEN || this->getType() == BISHOP) {
        // Diagonal lines
        directions.push_back(Field(1,1));
        directions.push_back(Field(-1,-1));
        directions.push_back(Field(-1,1));
        directions.push_back(Field(1,-1));
    }
    if(this->getType() == QUEEN || this->getType() == ROOK) {
        // Straigt lines
        directions.push_back(Field(1,0));
        directions.push_back(Field(-1,0));
        directions.push_back(Field(0,1));
        directions.push_back(Field(0,-1));
    }

    // Initialize possible moves
    for(auto &d : directions) {
        for(unsigned int i=1; i<8; i++) {
            // Obtain move position
            Field m = this->getPosition() + Field(d.getX()*i, d.getY()*i);

            if(this->moveOnboard(m)) {
                moves.push_back(m);
            } else {
                // Next positions should not be tried
                break;
            }
        }
    }

    return moves;
}