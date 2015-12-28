// Include standard library
#include <stdexcept>

// Include project files
#include "move.h"
#include "board.h"

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
        if(p == this->movingPiece || this->moveType == MT_CASTLING) {
            // TODO
        } else if(*p->getTile() == this->destination) {
            // TODO capture if opponent color
        } else {
            boardAfterMove.addPiece(p->getTile()->getX(), p->getTile()->getY(), p->getType(), p->getColor());
        }
    }

    if(this->movingPiece->getColor() == WHITE) {
        boardAfterMove.setActiveColor(BLACK);
    } else {
        boardAfterMove.setActiveColor(WHITE);
    }

    boardAfterMove.setBoardStatus(BS_UNKNOWN);

    return boardAfterMove;
}
