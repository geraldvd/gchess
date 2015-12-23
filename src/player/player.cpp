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

Player *Player::getOpponent()
{
    if(this->color == WHITE) {
        return this->board->getBlackPlayer();
    } else {
        return this->board->getWhitePlayer();
    }
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

bool Player::kingCheck() const
{

    return false;
}

void Player::updateMoves()
{
    vector<Move> moves{this->getPotentialMoves()};
    vector<Move> finalMoves;

    // Check moves w.r.t. board
    for(auto &m : moves) {
        switch(m.getMoveType()) {
        case MT_CASTLING:
            if(m.isValid() && m.getMoveType() == MT_CASTLING) {
                m.setValidity(this->isCastling(m));
            }
            break;
        default:
            break;
        }

        // Check whether this is a final move
        if(m.isValid()) {
            finalMoves.push_back(m);
        }
    }

    this->moves = finalMoves;

//    // Testing
//    vector<string> attackedTiles;
//    vector<string> occupiedTiles;
//    for(Tile* t : this->board.getTiles()) {
//        if(t->isOccupied()) occupiedTiles.push_back(t->getPositionString());
//        if(t->tileUnderAttack(this->getBoard())) attackedTiles.push_back(t->getPositionString());
//    }
//    cout << "Occupied tiles: ";
//    for(auto &s : occupiedTiles) cout << s << " ";
//    cout << endl;
//    cout << "Attacked tiles: ";
//    for(auto &s : attackedTiles) cout << s << " ";
//    cout << endl << endl;

//    // Check whether king is currently in check position
//    for(auto &p : this->getBoard()->getPieces()) {
//        if(p->getColor() == this->activePlayer && p->getType() == KING && p->getTile()->tileUnderAttack(this->getBoard())) {
//            // King check!
//            for(auto &movesOfPiece : moves) {
//                // Loop through all pieces
//                for(vector<Move>::iterator it=movesOfPiece.second.begin(); it!=movesOfPiece.second.end(); it++) {
//                    // Perform virtual move
//                    Game virtualGame(*this);
//                    if((*it).getMoveType() == MT_PROMOTION) {
//                        // TODO deal with this
//                    } else {
//                        virtualGame.move(movesOfPiece.first, (*it).get());
//                    }

//                    // Check check status
//                    if(virtualGame.getBoard()->getTile(p->getTile()->getPosition())->tileUnderAttack(virtualGame.getBoard())) {
//                        // Move not allowed
//                        //moves2[movesOfPiece.first].push_back((*it));
//                        movesOfPiece.second.erase(it);
//                    }
//                }
//            }
//            break;
//        }
//    }

}

std::vector<Move> Player::getPotentialMoves()
{
    vector<Move> moves;

    for(Tile* t : this->board->getTiles()) {
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

