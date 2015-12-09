#include "chesslabel.h"

const unsigned int ChessLabel::field_size = 50;

ChessLabel::ChessLabel(QWidget *parent) :
    ChessLabel(Field(0,0), parent)
{
}

ChessLabel::ChessLabel(const Field &f, QWidget *parent) :
    QLabel(parent)
{
    this->setField(f);
    this->setFixedWidth(ChessLabel::field_size);
    this->setFixedHeight(ChessLabel::field_size);
}

Field ChessLabel::getField() const
{
    return Field(this->x() / ChessLabel::field_size, 7 - this->y() / ChessLabel::field_size);
}

void ChessLabel::setField(const Field &f)
{
    this->move(f.first * ChessLabel::field_size, (7-f.second) * ChessLabel::field_size);
}

void ChessLabel::mousePressEvent(QMouseEvent *event)
{
    emit this->clicked();
}
