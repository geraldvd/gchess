// Include standard libraries
#include <utility>

// Include project files
#include "pawn.h"
#include "../board/board.h"

// Specify namespaces
using namespace std;

Pawn::Pawn(const PieceColor &c, const bool &justMovedDouble, const bool &hasMoved, Tile *parent) :
    Piece(PAWN, c, hasMoved, justMovedDouble, parent)
{
}

std::vector<Move> Pawn::calculateMoves(Board *b)
{
    // Initialize moves
    vector<Move> moves;

    // Check normal move and promotion
    int mx = this->getTile()->getX();
    int my = this->getColor()==WHITE ? this->getTile()->getY()+1 : this->getTile()->getY()-1;

    if(b->isOnBoard(mx, my) && !(b->getTile(mx, my)->isOccupied())) {
        // Check promotion
        if((this->getColor()==WHITE && my==7) || (this->getColor()==BLACK && my==0)) {
            moves.push_back(Move(mx, my, this->getTile()->getPiece(), MT_PROMOTION, PT_QUEEN));
            moves.push_back(Move(mx, my, this->getTile()->getPiece(), MT_PROMOTION, PT_ROOK));
            moves.push_back(Move(mx, my, this->getTile()->getPiece(), MT_PROMOTION, PT_BISHOP));
            moves.push_back(Move(mx, my, this->getTile()->getPiece(), MT_PROMOTION, PT_KNIGHT));
        } else {
            moves.push_back(Move(mx, my, this->getTile()->getPiece(), MT_NORMAL));
        }

        // Check jumps
        if(this->getColor() == WHITE && my==2) {
            my += 1;
        }
        if(this->getColor() == BLACK && my==5)
        {
            my -= 1;
        }
        if(b->isOnBoard(mx, my) && !(b->getTile(mx, my)->isOccupied())) {
            moves.push_back(Move(mx, my, this->getTile()->getPiece(), MT_PAWNJUMP));
        }
    }

    // Check capturing
    vector<int> captures = {
        1,
        -1
    };

    for(auto &c : captures) {
        if(this->getColor() == WHITE) {
            mx = this->getTile()->getX() + c;
            my = this->getTile()->getY() + 1;
        } else {
            mx = this->getTile()->getX() + c;
            my = this->getTile()->getY() - 1;
        }

        // Check whether caputring is allowed
        if(b->isOnBoard(mx, my) && b->getTile(mx, my)->isOccupied() && this->getColor() != b->getTile(mx, my)->getPiece()->getColor()) {
            // Check promotion
            if((this->getColor()==WHITE && my==7) || (this->getColor()==BLACK && my==0)) {
                moves.push_back(Move(mx, my, this->getTile()->getPiece(), MT_PROMOTION, PT_QUEEN));
                moves.push_back(Move(mx, my, this->getTile()->getPiece(), MT_PROMOTION, PT_ROOK));
                moves.push_back(Move(mx, my, this->getTile()->getPiece(), MT_PROMOTION, PT_BISHOP));
                moves.push_back(Move(mx, my, this->getTile()->getPiece(), MT_PROMOTION, PT_KNIGHT));
            } else {
                moves.push_back(Move(mx, my, this->getTile()->getPiece(), MT_NORMAL));
            }
        }
    }

    // Check En Passant
    if(b->isOnBoard(this->getTile()->getX()+1, this->getTile()->getY()) &&
            b->getTile(this->getTile()->getX()+1, this->getTile()->getY())->isOccupied() &&
            this->getColor() != b->getTile(this->getTile()->getX()+1, this->getTile()->getY())->getPiece()->getColor() &&
            b->getTile(this->getTile()->getX()+1, this->getTile()->getY())->getPiece()->getType() == PAWN) {
        Pawn* p = static_cast<Pawn*>(b->getTile(this->getTile()->getX()+1, this->getTile()->getY())->getPiece().get());
        if(p->getJustMovedDouble()) {
            if(p->getColor() == WHITE) {
                moves.push_back(Move(this->getTile()->getX()+1, this->getTile()->getY()-1, this->getTile()->getPiece(), MT_ENPASSANT));
            } else {
                moves.push_back(Move(this->getTile()->getX()+1, this->getTile()->getY()+1, this->getTile()->getPiece(), MT_ENPASSANT));
            }
        }
        // Reset justMovedDouble
        p->setJustMovedDouble(false);
    }
    if(b->isOnBoard(this->getTile()->getX()-1, this->getTile()->getY()) &&
            b->getTile(this->getTile()->getX()-1, this->getTile()->getY())->isOccupied() &&
            this->getColor() != b->getTile(this->getTile()->getX()-1, this->getTile()->getY())->getPiece()->getColor() &&
            b->getTile(this->getTile()->getX()-1, this->getTile()->getY())->getPiece()->getType() == PAWN) {
        Pawn* p = static_cast<Pawn*>(b->getTile(this->getTile()->getX()-1, this->getTile()->getY())->getPiece().get());
        if(p->getJustMovedDouble()) {
            if(p->getColor() == WHITE) {
                moves.push_back(Move(this->getTile()->getX()-1, this->getTile()->getY()-1, this->getTile()->getPiece(), MT_ENPASSANT));
            } else {
                moves.push_back(Move(this->getTile()->getX()-1, this->getTile()->getY()+1, this->getTile()->getPiece(), MT_ENPASSANT));
            }
        }
        // Reset justMovedDouble
        p->setJustMovedDouble(false);
    }

    return moves;
}

