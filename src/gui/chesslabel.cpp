#include "chesslabel.h"
#include "board/board.h"

const unsigned int ChessLabel::field_size = 50;

ChessLabel::ChessLabel(QWidget *parent) :
    ChessLabel(0, parent)
{
}

ChessLabel::ChessLabel(const unsigned int &f, QWidget *parent) :
    QLabel(parent)
{
    this->setPosition(f);
    this->setFixedWidth(ChessLabel::field_size);
    this->setFixedHeight(ChessLabel::field_size);
}

unsigned int ChessLabel::getPosition() const
{
    return this->x() / ChessLabel::field_size + 8 * (7 - this->y() / ChessLabel::field_size);
}

void ChessLabel::setPosition(const unsigned int &f)
{
    this->move(f%8 * ChessLabel::field_size, (7-((f-f%8)/8)) * ChessLabel::field_size);
}

void ChessLabel::mousePressEvent(QMouseEvent *event)
{
    emit this->clicked();
}
