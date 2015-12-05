#ifndef PIECELABEL_H
#define PIECELABEL_H

#include <QLabel>
#include <QString>

#include "game.h"

/**
 * @brief PieceLabel class inherits from QLabel. Goal: clickable, and contains pointer to piece
 */
class PieceLabel : public QLabel
{
    Q_OBJECT

public:
    // Constructor and destructor
    explicit PieceLabel(QWidget* parent=0);
    explicit PieceLabel(Piece* p, QWidget* parent=0);
    explicit PieceLabel(const QString & squareColor, QWidget* parent=0);
    explicit PieceLabel(Piece* p, const QString & squareColor, QWidget *parent);
    ~PieceLabel();

    // Getters and setters
    Piece* getPiece() const;
    QString getSquareColor() const;
    void setSquareColor(const QString & squareColor);
    Field getField() const;

signals:
    void clicked();



protected:
    void mousePressEvent(QMouseEvent* event);

private:
    // Piece on this label
    Piece* piece;

    // Color of square (if applicable)
    QString squareColor;
};

#endif // PIECELABEL_H
