// Include standard library
#include <stdexcept>
#include <iostream>

// Include project files
#include "move.h"
#include "board.h"
#include "../piece/pawn.h"
#include "../piece/king.h"

// Specify namespaces
using namespace std;

Move::Move(const Field &f, Piece_ptr movingPiece, const MoveType &mt, const PromotionType &pt) :
    Move(f.getX(), f.getY(), movingPiece, mt, pt)
{
}

Move::Move(const int &x, const int &y, Piece_ptr movingPiece, const MoveType &mt, const PromotionType &pt) :
    moveType(mt),
    movingPiece(movingPiece),
    destination(Field(x, y)),
    castlingRookPosition(0),
    promotionType(pt)
{
}

MoveType Move::getMoveType() const
{
    return this->moveType;
}

Field Move::getCastlingRookPosition() const
{
    return this->castlingRookPosition;
}

void Move::setMoveType(const MoveType &mt)
{
    this->moveType = mt;
}

void Move::setCastlingRookPosition(const Field &position)
{
    this->castlingRookPosition = position;
}

PromotionType Move::getPromotionType() const
{
    return this->promotionType;
}

void Move::setPromotionType(const PromotionType &pt)
{
    this->promotionType = pt;
}

Piece_ptr Move::getMovingPiece() const
{
    return this->movingPiece;
}

Field Move::getDestination() const
{
    return this->destination;
}

Board Move::execute(Board *b)
{
    Board boardAfterMove;

    for(auto &p : b->getPieces()) {
        // Castling rook movement
        if(this->moveType == MT_CASTLING && p->getType() == ROOK && p->getColor() == this->getMovingPiece()->getColor() && *(p->getTile()) == this->castlingRookPosition) {
            if(this->destination.getX() == NUM_TILES_X-2) {
                boardAfterMove.addPiece(this->destination.getX()-1, this->destination.getY(), ROOK, p->getColor());
            } else {
                boardAfterMove.addPiece(this->destination.getX()+1, this->destination.getY(), ROOK, p->getColor());
            }
            continue;
        }

        // Place moving piece
        if(p->getTile() == this->movingPiece->getTile()) {
            if(this->moveType == MT_PROMOTION) {
                switch(this->promotionType) {
                case PT_QUEEN:
                    boardAfterMove.addPiece(destination.getX(), destination.getY(), QUEEN, p->getColor(), true);
                    break;
                case PT_ROOK:
                    boardAfterMove.addPiece(destination.getX(), destination.getY(), ROOK, p->getColor(), true);
                    break;
                case PT_BISHOP:
                    boardAfterMove.addPiece(destination.getX(), destination.getY(), BISHOP, p->getColor(), true);
                    break;
                case PT_KNIGHT:
                    boardAfterMove.addPiece(destination.getX(), destination.getY(), KNIGHT, p->getColor(), true);
                    break;
                default:
                    throw domain_error("Unknown promotion type.");
                    break;
                }
            } else if(this->moveType == MT_PAWNJUMP) {
                boardAfterMove.addPiece(destination.getX(), destination.getY(), p->getType(), p->getColor(), true, true);
            }
            else {
                boardAfterMove.addPiece(destination.getX(), destination.getY(), p->getType(), p->getColor(), true, false);
            }
            continue;
        }


        // En passant captured piece
        if(p->getType() == PAWN && this->moveType == MT_ENPASSANT && p->getColor() != this->getMovingPiece()->getColor() && p->getTile()->getX() == this->destination.getX() &&
                ((p->getColor() == WHITE && p->getTile()->getY()+1 == this->destination.getY()) || (p->getColor() == BLACK && p->getTile()->getY()-1 == this->destination.getY()))) {
            // Piece is captured
            continue;
        }

        // Captured piece
        if(this->destination == *(p->getTile())) {
            // Piece is captured
            continue;
        }

        // Other pieces
        boardAfterMove.addPiece(p->getTile()->getX(), p->getTile()->getY(), p->getType(), p->getColor());
    }

    // Set moved
    this->movingPiece->setMoved(true);

    // Set active piece
    if(this->movingPiece->getColor() == WHITE) {
        boardAfterMove.setActivePlayer(BLACK);
    } else {
        boardAfterMove.setActivePlayer(WHITE);
    }

    // Set boardstatus
    boardAfterMove.calculatePotentialMoves();
    if(boardAfterMove.getActiveKing()->getTile()->attackingPieces(&boardAfterMove, boardAfterMove.getInActivePlayer()).size() != 0) {
        if(boardAfterMove.getActivePlayer() == WHITE) {
            boardAfterMove.setBoardStatus(BS_CHECKWHITE);
        } else {
            boardAfterMove.setBoardStatus(BS_CHECKBLACK);
        }
    } else {
        boardAfterMove.setBoardStatus(BS_NORMAL);
    }

    return boardAfterMove;
}

unsigned int Move::getHash() const
{
    unsigned int h = 31;
    h = (h*HASH_A) ^ (this->moveType*HASH_B);
    h = (h*HASH_A) ^ (this->movingPiece->getHash()*HASH_B);
    h = (h*HASH_A) ^ (this->destination.getHash()*HASH_B);
    h = (h*HASH_A) ^ (this->castlingRookPosition.getHash()*HASH_B);
    h = (h*HASH_A) ^ (this->promotionType*HASH_B);

    return h % HASH_C;
}

string Move::getMoveString() const
{
    //cout << this->getMovingPiece()->getTile()->getPositionString() << " + " << this->destination.getPositionString() << endl;
    return string(this->getMovingPiece()->getTile()->getPositionString() + " to " + this->destination.getPositionString());
}
