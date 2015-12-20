// Include standard libraries
#include <utility>

// Include project files
#include "pawn.h"
#include "board/board.h"

// Specify namespaces
using namespace std;

Pawn::Pawn(const unsigned int &position, const PieceColor &c, const bool &hasMoved, const bool &justMovedDouble) :
    Piece(position, c, hasMoved),
    justMovedDouble(justMovedDouble)
{
    this->type = PAWN;
}

bool Pawn::getJustMovedDouble() const
{
    return this->justMovedDouble;
}

std::vector<Move> Pawn::calculateMoves(Board *b)
{
    // Initialize moves
    vector<Move> moves;

    // Check normal move and promotion
    unsigned int m = this->getPosition();
    if(this->getColor() == WHITE) {
        m += 8;
    } else {
        m -= 8;
    }
    if(b->isOnBoard(m) && !(b->getTile(m)->isOccupied())) {
        // Check promotion
        if((this->getColor()==WHITE && m<8) || (this->getColor()==BLACK && m>55)) {
            moves.push_back(Move(m, MT_PROMOTION_QUEEN));
            moves.push_back(Move(m, MT_PROMOTION_ROOK));
            moves.push_back(Move(m, MT_PROMOTION_BISHOP));
            moves.push_back(Move(m, MT_PROMOTION_KNIGHT));
        } else {
            moves.push_back(Move(m, MT_NORMAL));
        }
    }

    // Check jumps
    if(!this->has_moved) {
        m = this->getPosition();
        if(this->getColor() == WHITE && m>7 && m<16) {
            m += 16;
        }
        if(this->getColor() == BLACK && m>48 && m<56)
        {
            m -= 16;
        }

        if(b->isOnBoard(m) && !(b->getTile(m)->isOccupied())) {
            moves.push_back(Move(m, MT_NORMAL));
        }
    }

    // Check capturing
    vector<pair<unsigned int, unsigned int> > captures = {
        pair<unsigned int, unsigned int>(1,1),
        pair<unsigned int, unsigned int>(-1,1)
    };

    for(auto &c : captures) {
        if(this->getColor() == WHITE) {
            m = this->getPosition() + c.first + 8*c.second;
        } else {
            m = this->getPosition() - c.first - 8*c.second;
        }

        // Check whether caputring is allowed
        if(b->isOnBoard(m) && b->getTile(m)->isOccupied() && this->getColor() != b->getTile(m)->getPiece()->getColor()) {
            // TODO check king
            moves.push_back(Move(m, MT_NORMAL));
        }
    }

    // Check En Passant
    if(b->isOnBoard(this->getPosition() + 1) && b->getTile(this->getPosition() + 1)->isOccupied() &&
            this->getColor() != b->getTile(this->getPosition() + 1)->getPiece()->getColor() && b->getTile(this->getPosition() + 1)->getPiece()->getType() == PAWN) {
        Pawn* p = static_cast<Pawn*>(b->getTile(this->getPosition() + 1)->getPiece().get());
        if(p->getJustMovedDouble()) {
            moves.push_back(Move(this->getPosition() + 1, MT_ENPASSANT));
        }
    }
    if(b->isOnBoard(this->getPosition() - 1) && b->getTile(this->getPosition() - 1)->isOccupied() &&
            this->getColor() != b->getTile(this->getPosition() - 1)->getPiece()->getColor() && b->getTile(this->getPosition() - 1)->getPiece()->getType() == PAWN) {
        Pawn* p = static_cast<Pawn*>(b->getTile(this->getPosition() - 1)->getPiece().get());
        if(p->getJustMovedDouble()) {
            moves.push_back(Move(this->getPosition() - 1, MT_ENPASSANT));
        }
    }
    return moves;
}

