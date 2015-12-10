#include "pawn.h"

using namespace std;

Pawn::Pawn(const int & x, const int & y, const PieceColor & c, const bool & hasMoved, const bool & justMovedDouble) :
    Piece(x, y, c, hasMoved),
    justMovedDouble(justMovedDouble)
{
    this->type = PAWN;
}

void Pawn::findMoves(const std::vector<Piece*> & pieces)
{
    // TODO en passant capturing + reaching other side of board


    // Initialize moves
    vector<Field> moves;
    this->moves = vector<Move>();

    // Reset check status
    this->otherKingCheck = false;

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
            this->moves.push_back(Move(m, NORMAL));
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
            if(p->getPosition() == m && p->getColor() != this->getColor()) {
                if(p->getType() != KING) {
                    // Piece can be captured
                    this->moves.push_back(Move(m, NORMAL));
                } else {
                    // King check!
                    this->otherKingCheck = true;
                }
            }
        }
    }
}

