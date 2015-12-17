#include "pawn.h"

using namespace std;

Pawn::Pawn(const Field &f, const PieceColor & c, const bool & hasMoved, const bool & justMovedDouble) :
    Piece(f, c, hasMoved),
    justMovedDouble(justMovedDouble)
{
    this->type = PAWN;
}

vector<Field> Pawn::getMoves(const std::map<Field, Piece *> &pieces, const bool &king_check)
{
//    // TODO en passant capturing + reaching other side of board


//    // Initialize moves
//    vector<Field> moves;
//    this->moves = vector<Move>();

//    // Reset check status
//    this->otherKingCheck = false;

//    // List all potiontially possible moves
//    if(this->getColor() == WHITE) {
//        // WHITE
//        moves.push_back(this->getPosition() + Field(0,1));
//        if(this->getPosition().second == 1) {
//            // Pawn did not move yet
//            moves.push_back(this->getPosition() + Field(0,2));
//        }
//    } else {
//        // BLACK
//        moves.push_back(this->getPosition() + Field(0,-1));
//        if(this->getPosition().second == 6) {
//            // Pawn did not move yet
//            moves.push_back(this->getPosition() + Field(0,-2));
//        }
//    }

//    // Check whether moves can be made
//    bool valid{true};
//    for(auto &m : moves) {
//        for(auto &p: pieces) {
//            if(m == p->getPosition()) {
//                valid = false;
//            }
//        }
//        if(valid && this->moveOnboard(m)) {
//            // Check promotion
//            if((this->getColor() == WHITE && m.second==7) || ((this->getColor() == BLACK && m.second==0))) {
//                // Pawn promotion!
//                this->moves.push_back(Move(m, PROMOTION_QUEEN));
//                this->moves.push_back(Move(m, PROMOTION_ROOK));
//                this->moves.push_back(Move(m, PROMOTION_KNIGHT));
//                this->moves.push_back(Move(m, PROMOTION_BISHOP));
//            } else {
//                this->moves.push_back(Move(m, NORMAL));
//            }
//        }
//    }

//    // Check diagonal capture
//    moves = vector<Field>();
//    if(this->getColor() == WHITE) {
//        // WHITE
//        moves.push_back(Field(this->getPosition() + Field(1,1)));
//        moves.push_back(Field(this->getPosition() + Field(-1,1)));
//    } else {
//        // BLACK
//        moves.push_back(Field(this->getPosition() + Field(1,-1)));
//        moves.push_back(Field(this->getPosition() + Field(-1,-1)));
//    }
//    for(auto &m : moves) {
//        for(auto &p : pieces) {
//            if(p->getPosition() == m && p->getColor() != this->getColor()) {
//                if(p->getType() != KING) {
//                    // Piece can be captured
//                    this->moves.push_back(Move(m, NORMAL));
//                } else {
//                    // King check!
//                    this->otherKingCheck = true;
//                }
//            }
//        }
    //    }
    return vector<Field>();
}

std::vector<Field> Pawn::getPotentialMoves()
{
    // Initialize moves
    vector<Field> moves;

    // List all potiontially possible moves
    if(this->getColor() == WHITE) {
        // WHITE
        moves.push_back(this->getPosition() + Field(0,1));
        if(this->getPosition().getY() == 1) {
            // Pawn did not move yet
            moves.push_back(this->getPosition() + Field(0,2));
        }
    } else {
        // BLACK
        moves.push_back(this->getPosition() + Field(0,-1));
        if(this->getPosition().getY() == 6) {
            // Pawn did not move yet
            moves.push_back(this->getPosition() + Field(0,-2));
        }
    }

    return moves;
}

