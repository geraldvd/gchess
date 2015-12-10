#include "linepiece.h"

using namespace std;

LinePiece::LinePiece(const int & x, const int & y, const PieceColor & c, const bool & hasMoved) :
    Piece(x, y, c, hasMoved)
{
}

void LinePiece::findMoves(const std::vector<Piece *> & pieces)
{
    // Initialize moves
    vector<Field> moves;

    // Store whether line is blocked, and whether move is still valid
    vector<pair<Field,bool> > directions;
    if(this->getType() == QUEEN || this->getType() == BISHOP) {
        // Diagonal lines
        directions.push_back(pair<Field,bool>(Field(1,1), true));
        directions.push_back(pair<Field,bool>(Field(-1,-1), true));
        directions.push_back(pair<Field,bool>(Field(-1,1), true));
        directions.push_back(pair<Field,bool>(Field(1,-1), true));
    }
    if(this->getType() == QUEEN || this->getType() == ROOK) {
        // Straigt lines
        directions.push_back(pair<Field,bool>(Field(1,0), true));
        directions.push_back(pair<Field,bool>(Field(-1,0), true));
        directions.push_back(pair<Field,bool>(Field(0,1), true));
        directions.push_back(pair<Field,bool>(Field(0,-1), true));
    }

    // Initialize possible moves - only diagonals
    for(int i=1; i<8; i++) {
        for(auto &d : directions) {
            // Check whether line was already occupied
            if(d.second) {
                Field m = this->getPosition() + Field(d.first.first*i, d.first.second*i);

                if(this->moveOnboard(m)) {
                    for(auto &p : pieces) {
                        if(m == p->getPosition()) {
                            if(p->getColor() == this->getColor()) {
                                // Same color: don't add and don't continue with line
                                d.second = false;
                                break; // Stop looping through pieces
                            } else {
                                // Opponent check move!
                                if(p->getType() != KING) {
                                    // Piece can be taken! Don't continue; piece cannot be passed
                                    d.second = false;
                                    moves.push_back(m);
                                    break; // Stop looping through pieces
                                }
                            }
                        }
                    }
                    // Free place, so allowed
                    if(d.second) {
                        moves.push_back(m);
                    }
                } else {
                    // Next positions should not be tried
                    d.second = false;
                }
            }
        }
    }

    // Check whether moves are still on board
    this->moves = moves;
}

