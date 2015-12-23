// Include standard libraries
#include <algorithm>
#include <string>
#include <iostream>

// Include project files
#include "gamemanager.h"
#include "piece/pawn.h"
#include "piece/queen.h"
#include "piece/rook.h"
#include "piece/bishop.h"
#include "piece/knight.h"

// Specify namespaces
using namespace std;

GameManager::GameManager() :
    board(Board(2))
{

}

Board *GameManager::getBoard()
{
    return &this->board;
}

MoveStatus GameManager::move(Move &m)
{
    MoveStatus moveStatus = this->board.getActivePlayer()->move(m);
    if(moveStatus == MS_PROMOTION) {
        // If promotion was not specified before, assume Queen
        m.setPromotionType(PT_QUEEN);
        moveStatus = this->board.getActivePlayer()->doPromotion(m);
    }

    if(moveStatus == MS_OK) {
        // Update game
        this->board.switchPlayer();
        this->board.getActivePlayer()->getOpponent()->updateMoves(); // TODO updateMoves? Or look at all potential moves?
        this->board.getActivePlayer()->updateMoves();
    }
    return moveStatus;
}

MoveStatus GameManager::move(const Field &from, const Field &to)
{
    for(auto &m : this->getBoard()->getActivePlayer()->getMoves()) {
        if(static_cast<Field>(m) == to && static_cast<Field>(*m.getMovingPiece()->getTile()) == from) {
            return this->move(m);
        }
    }
    return MS_INVALID;
}
