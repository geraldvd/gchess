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
    color(color),
    board(board),
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

void Player::setColor(const PieceColor &color)
{
    this->color = color;
}
Board *Player::getBoard()
{
    return this->board;
}

