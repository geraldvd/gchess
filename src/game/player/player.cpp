// Include standard libraries
#include <stdexcept>

// Include project files
#include "board/board.h"
#include "piece/king.h"
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

std::vector<Move> Player::getPossibleMoves()
{
    vector<Move> moves{this->getPotentialMoves()};
    vector<Move> finalMoves;

    // Check moves w.r.t. board
    for(auto &m : moves) {
        switch(m.getMoveType()) {
        case MT_CASTLING:
            if(m.isValid() && m.getMoveType() == MT_CASTLING) {
                m.setValidity(this->isCasting(m));
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

    return finalMoves;

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

bool Player::isCasting(const Move &m)
{
    if(m.getMovingPiece()->getType() != KING || m.getMoveType() != MT_CASTLING ||
            m.getCastlingRookPosition().getY() != m.getY()) {
        return false;
    }

    int step = m.getX() < m.getCastlingRookPosition().getX() ? 1 : -1;
    for(int i=m.getX()+1; i<m.getCastlingRookPosition().getX(); i+= step) {
        if(this->getBoard()->getTile(i, m.getY())->tileUnderAttack(this->getBoard())) {
            return false;
        }
    }

    // All checks passed
    return true;
}

