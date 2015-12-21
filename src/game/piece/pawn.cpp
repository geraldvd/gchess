// Include standard libraries
#include <utility>

// Include project files
#include "pawn.h"
#include "board/board.h"

// Specify namespaces
using namespace std;

Pawn::Pawn(const PieceColor &c, const bool &hasMoved, const bool &justMovedDouble, Tile *parent) :
    Piece(PAWN, c, hasMoved, parent),
    justMovedDouble(justMovedDouble)
{
}

bool Pawn::getJustMovedDouble() const
{
    return this->justMovedDouble;
}

void Pawn::setJustMovedDouble(const bool &d)
{
    this->justMovedDouble = d;
}

std::vector<Move> Pawn::calculateMoves(Board *b)
{
    // Initialize moves
    vector<Move> moves;

    // Check normal move and promotion
    unsigned int m = this->getTile()->getPosition();
    if(this->getColor() == WHITE) {
        m += 8;
    } else {
        m -= 8;
    }
    if(b->isOnBoard(m) && !(b->getTile(m)->isOccupied())) {
        // Check promotion
        if((this->getColor()==WHITE && m>55) || (this->getColor()==BLACK && m<8)) {
            moves.push_back(Move(m, MT_PROMOTION));
        } else {
            moves.push_back(Move(m, MT_NORMAL));
        }

        // Check jumps
        if(this->getColor() == WHITE && m>=16 && m<24) {
            m += 8;
        }
        if(this->getColor() == BLACK && m>=40 && m<48)
        {
            m -= 8;
        }
        if(b->isOnBoard(m) && !(b->getTile(m)->isOccupied())) {
            moves.push_back(Move(m, MT_PAWNJUMP));
        }
    }

    // Check capturing
    vector<pair<unsigned int, unsigned int> > captures = {
        pair<unsigned int, unsigned int>(1,1),
        pair<unsigned int, unsigned int>(-1,1)
    };

    for(auto &c : captures) {
        if(this->getColor() == WHITE) {
            m = this->getTile()->getPosition() + c.first + 8*c.second;
        } else {
            m = this->getTile()->getPosition() - c.first - 8*c.second;
        }

        // Check whether caputring is allowed
        if(b->isOnBoard(m) && b->getTile(m)->isOccupied() && this->getColor() != b->getTile(m)->getPiece()->getColor()) {
            // TODO check king

            // Check promotion
            if((this->getColor()==WHITE && m>55) || (this->getColor()==BLACK && m<8)) {
                moves.push_back(Move(m, MT_PROMOTION));
            } else {
                moves.push_back(Move(m, MT_NORMAL));
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
                moves.push_back(Move(this->getTile()->getX()+1, this->getTile()->getY()-1, MT_ENPASSANT));
            } else {
                moves.push_back(Move(this->getTile()->getX()+1, this->getTile()->getY()+1, MT_ENPASSANT));
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
                moves.push_back(Move(this->getTile()->getX()-1, this->getTile()->getY()-1, MT_ENPASSANT));
            } else {
                moves.push_back(Move(this->getTile()->getX()-1, this->getTile()->getY()+1, MT_ENPASSANT));
            }
        }
        // Reset justMovedDouble
        p->setJustMovedDouble(false);
    }

    return moves;
}

