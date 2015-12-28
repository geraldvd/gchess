// Include standard libraries
#include <stdexcept>
#include <algorithm>

// Include project files
#include "../board/board.h"
#include "../piece/king.h"
#include "../piece/pawn.h"
#include "player.h"

// Specify namespaces
using namespace std;

Player::Player()
{

}

Player::Player(const PieceColor &color, Board *board) :
    board(board),
    color(color),
    king(NULL)
{
    for(auto &p : this->board->getPieces()) {
        if(p->getColor() == this->color && p->getType() == KING) {
            this->king = dynamic_pointer_cast<King>(p);
        }
    }

    // Check whether king is onboard
    if(this->king == NULL) {
        throw runtime_error("Player does not have a king.");
    }
}
PieceColor Player::getColor() const
{
    return this->color;
}

string Player::getColorString() const
{
    if(this->color == WHITE) {
        return "white";
    } else {
        return "black";
    }
}

void Player::setColor(const PieceColor &color)
{
    this->color = color;
}
Board *Player::getBoard()
{
    return this->board;
}

std::vector<Move> Player::getMoves() const
{
    return this->moves;
}

MoveStatus Player::move(const Move &m)
{
    if(find(this->moves.begin(), this->moves.end(), m) == this->moves.end()) {
        return MS_INVALID;
    }

    // Check pawn double moves (for En Passant capturing)
    if(m.getMovingPiece()->getType() == PAWN) {
        Pawn* p = static_cast<Pawn*>(m.getMovingPiece().get());
        if(m.getMoveType() == MT_PAWNJUMP) {
            p->setJustMovedDouble(true);
        } else {
            p->setJustMovedDouble(false);
        }
    }

    // Perform move
    switch(m.getMoveType()) {
    case MT_PROMOTION:
        if(m.getPromotionType() == PT_NONE) {
            return MS_PROMOTION;
        } else {
            return this->doPromotion(m);
        }
        break;
    case MT_CASTLING:
    {
        // Move king
        Field from = this->getKing()->getTile()->getPosition();
        this->getBoard()->getTile(m.getPosition())->setPiece(this->getKing());
        this->getBoard()->getTile(from)->clearPiece();
        // Move rook
        if(m.getX() == NUM_TILES_X-2) {
            // King moved to the right
            this->getBoard()->getTile(m.getX()-1, m.getY())->setPiece(this->getBoard()->getTile(m.getX()+1, m.getY())->getPiece());
            this->getBoard()->getTile(m.getX()+1, m.getY())->clearPiece();
        } else {
            this->getBoard()->getTile(m.getX()+1, m.getY())->setPiece(this->getBoard()->getTile(m.getX()-2, m.getY())->getPiece());
            this->getBoard()->getTile(m.getX()-2, m.getY())->clearPiece();
        }
    }
        break;
    case MT_ENPASSANT:
    {
        // Capture opponent pawn
        if(m.getMovingPiece()->getColor() == WHITE) {
            this->getBoard()->getTile(m.getX(), m.getY()-1)->clearPiece();
        } else {
            this->getBoard()->getTile(m.getX(), m.getY()+1)->clearPiece();
        }
    }
    default:
    {
        Field from = m.getMovingPiece()->getTile()->getPosition();
        this->getBoard()->getTile(m.getX(), m.getY())->setPiece(m.getMovingPiece());
        this->getBoard()->getTile(from)->clearPiece();
    }
        break;
    }

    m.getMovingPiece()->setMoved();
    return MS_OK;
}

MoveStatus Player::move(const Field &from, const Field &to)
{
    for(auto &m : this->moves) {
        if(*m.getMovingPiece()->getTile() == from && m.getDestination() == to) {
            return this->move(m);
        }
    }
    return MS_INVALID;
}

MoveStatus Player::doPromotion(const Move &m)
{
    if(m.getMoveType() != MT_PROMOTION) {
        return MS_INVALID;
    }

    switch(m.getPromotionType()) {
    case PT_QUEEN:
        this->getBoard()->addPiece(m.getX(), m.getY(), QUEEN, this->color);
        break;
    case PT_ROOK:
        this->getBoard()->addPiece(m.getX(), m.getY(), ROOK, this->color);
        break;
    case PT_BISHOP:
        this->getBoard()->addPiece(m.getX(), m.getY(), BISHOP, this->color);
        break;
    case PT_KNIGHT:
        this->getBoard()->addPiece(m.getX(), m.getY(), KNIGHT, this->color);
        break;
    default:
        throw invalid_argument("Promotion type unknown.");
        break;
    }
    m.getMovingPiece()->getTile()->clearPiece();

    m.getMovingPiece()->setMoved();
    return MS_OK;
}

std::shared_ptr<King> Player::getKing()
{
    return this->king;
}

bool Player::kingCheck()
{
    switch(this->getBoard()->getBoardStatus()) {
    case BS_CHECKWHITE:
    case BS_CHECKMATEWHITE:
        if(this->color == WHITE) {
            return true;
        }
        break;
    case BS_CHECKBLACK:
    case BS_CHECKMATEBLACK:
        if(this->color == BLACK) {
            return true;
        }
        break;
    default:
        break;
    }
    return false;
}

void Player::updateMoves()
{
    vector<Move> moves{this->getPotentialMoves()};
    vector<Move> finalMoves;

    for(auto &m : moves) {
        // Check castling
        if(m.getMoveType() == MT_CASTLING) {
            if(! this->isCastling(m)) {
                 break;
            }
        }

        // Virtual move execution
        Board boardAfterMove = m.execute(this->getBoard());

        // CHECK status
        for(auto &p : boardAfterMove.getPieces())
        if(this->king->getTile()->tileUnderAttack(this->getOpponent())) {
            if(this->color == WHITE) {
                this->getBoard()->setBoardStatus(BS_CHECKWHITE);
            } else {
                this->getBoard()->setBoardStatus(BS_CHECKBLACK);
            }
        } else {
            this->getBoard()->setBoardStatus(BS_NORMAL);
        }
    }


    // Checkmate or stalemate?
    if(finalMoves.size() == 0) {
        if(this->kingCheck()) {
            if(this->color == WHITE) {
                this->getBoard()->setBoardStatus(BS_CHECKMATEWHITE);
            } else {
                this->getBoard()->setBoardStatus(BS_CHECKMATEBLACK);
            }
        } else {
            this->getBoard()->setBoardStatus(BS_STALEMATE);
        }
    }

    this->moves = finalMoves;
}

std::vector<Move> Player::getPotentialMoves()
{
    vector<Move> moves;

    for(auto t : this->board->getTiles()) {
        if(t->isOccupied() && t->getPiece()->getColor() == this->color) {
            vector<Move> pieceMoves = t->getPiece()->calculateMoves(this->getBoard());
            moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
        }
    }

    return moves;
}

bool Player::isCastling(const Move &m)
{
    if(m.getMovingPiece()->getType() != KING || m.getMoveType() != MT_CASTLING ||
            m.getCastlingRookPosition().getY() != m.getY()) {
        return false;
    }

    int istep = m.getMovingPiece()->getTile()->getX() < m.getCastlingRookPosition().getX() ? 1 : -1;
    int istart = m.getMovingPiece()->getTile()->getX()+istep;
    int iend = istart + 2*istep;
    for(int i=istart; istep*i<istep*iend; i+= istep) {
        if(this->getBoard()->getTile(i, m.getY())->tileUnderAttack(this->getOpponent())) {
            return false;
        }
    }

    // All checks passed
    return true;
}

