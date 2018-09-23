// Include standard libraries
#include <stdexcept>
#include <algorithm>
#include <iostream>

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

Board Player::move(Move &m)
{
    if(find(this->moves.begin(), this->moves.end(), m) == this->moves.end()) {
        return *this->getBoard();
    } else {
        return m.execute(this->getBoard());
    }
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
    // TODO setmoved
    vector<Move> moves{this->getPotentialMoves()};
    vector<Move> finalMoves;

    for(auto &m : moves) {
        // Virtual move execution
        Board boardAfterMove = m.execute(this->getBoard());

        // CHECK status
        if(boardAfterMove.getActivePlayer()->getOpponent()->getKing()->getTile()->attackingPieces(boardAfterMove.getActivePlayer()).size() != 0) {
            // Not allowed, moving into check
            continue;
        }

        // Add move to  allowed moves
        finalMoves.push_back(m);
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

    for(auto &t : this->board->getTiles()) {
        if(t->isOccupied() && t->getPiece()->getColor() == this->color) {
            vector<Move> pieceMoves = t->getPiece()->calculateMoves(this->getBoard());
            moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
        }
    }

    return moves;
}

