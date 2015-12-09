#include "pawn.h"

using namespace std;

Pawn::Pawn(const int & x, const int & y, const PieceColor & c, const bool & hasMoved, const bool & justMovedDouble) :
    Piece(x, y, c, hasMoved),
    justMovedDouble(justMovedDouble)
{
    this->type = "Pawn";
}

void Pawn::findMoves(const std::vector<Piece*> & pieces)
{
    // Initialize moves
    vector<Field> moves;
    this->moves = vector<Field>();

    // List all potiontially possible moves
    if(this->getColor() == WHITE) {
        // WHITE
        moves.push_back(this->getPosition() + Field(0,1));
        if(this->getPosition().second == 1) {
            // Pawn did not move yet
            moves.push_back(this->getPosition() + Field(0,2));
        }
    } else {
        // BLACK
        moves.push_back(this->getPosition() + Field(0,-1));
        if(this->getPosition().second == 6) {
            // Pawn did not move yet
            moves.push_back(this->getPosition() + Field(0,-2));
        }
    }

    // Check whether moves can be made
    bool valid{true};
    for(auto &m : moves) {
        for(auto &p: pieces) {
            if(m == p->getPosition()) {
                valid = false;
            }
        }
        if(valid && this->moveOnboard(m)) {
            this->moves.push_back(m);
        }
    }

    // Check diagonal capture
    moves = vector<Field>();
    if(this->getColor() == WHITE) {
        // WHITE
        moves.push_back(Field(this->getPosition() + Field(1,1)));
        moves.push_back(Field(this->getPosition() + Field(-1,1)));
    } else {
        // BLACK
        moves.push_back(Field(this->getPosition() + Field(1,-1)));
        moves.push_back(Field(this->getPosition() + Field(-1,-1)));
    }
    for(auto &m : moves) {
        for(auto &p : pieces) {
            if(p->getPosition() == m && p->getColor() != this->getColor() && p->getType() != "King") {
                this->moves.push_back(m);
            }
        }
    }
}

