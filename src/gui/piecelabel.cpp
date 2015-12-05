#include "piecelabel.h"
#include "chessboard.h"

PieceLabel::PieceLabel(QWidget *parent) :
    PieceLabel(NULL, QString(), parent)
{

}

PieceLabel::PieceLabel(Piece *p, QWidget *parent) :
    PieceLabel(p, QString(), parent)
{

}

PieceLabel::PieceLabel(const QString & squareColor, QWidget *parent) :
    PieceLabel(NULL, squareColor, parent)
{

}

PieceLabel::PieceLabel(Piece* p, const QString & squareColor, QWidget *parent) :
    QLabel(parent),
    piece(p),
    squareColor(squareColor)
{

}

PieceLabel::~PieceLabel()
{
    // Don't delete piece; will be done in game class
}

Piece *PieceLabel::getPiece() const
{
    return this->piece;
}

void PieceLabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}

void PieceLabel::setSquareColor(const QString & squareColor)
{
    this->squareColor = squareColor;
}

Field PieceLabel::getField() const
{
    return Field(this->x() * 8 / Chessboard::pixelSizeBoard, 7 - this->y() * 8 / Chessboard::pixelSizeBoard);
}

QString PieceLabel::getSquareColor() const
{
    return this->squareColor;
}
