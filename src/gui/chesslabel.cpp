#include "chesslabel.h"
#include "board/board.h"

const unsigned int ChessLabel::field_size = 50;

ChessLabel::ChessLabel(QWidget *parent) :
    ChessLabel(0, parent)
{
}

ChessLabel::ChessLabel(const unsigned int &f, QWidget *parent) :
    QLabel(parent),
    pieceMove()
{
    this->setPosition(f);
    this->setFixedWidth(ChessLabel::field_size);
    this->setFixedHeight(ChessLabel::field_size);
}

Field ChessLabel::getPosition() const
{
    // TODO check 7-y...
    return Field(this->x() / ChessLabel::field_size, 7 - (this->y() / ChessLabel::field_size));
}

void ChessLabel::setPosition(const unsigned int &f)
{
    this->move(f%8 * ChessLabel::field_size, (7-((f-f%8)/8)) * ChessLabel::field_size);
}

void ChessLabel::setMove(const Move &m)
{
    this->pieceMove = m;
}

bool ChessLabel::hasMove() const
{
    if(this->pieceMove.getMoveType() == MT_NONE) {
        return false;
    }
    return true;
}

Move *ChessLabel::getMove()
{
    if(this->pieceMove.getMoveType() != MT_NONE) {
        return &this->pieceMove;
    }
    return NULL;
}

void ChessLabel::mousePressEvent(QMouseEvent *event)
{
    emit this->clicked();
}
