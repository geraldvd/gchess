#ifndef CHESSLABEL_H
#define CHESSLABEL_H

// Include Qt library
#include <QLabel>

// Include project libraries
#include "game.h"

/**
 * @brief ChessLabel class inherits from QLabel. Goal: clickable, contains chess field locations
 */
class ChessLabel : public QLabel
{
    Q_OBJECT
public:
    // Constructors
    explicit ChessLabel(QWidget* parent=0);
    explicit ChessLabel(const Field &f, QWidget *parent=0);

    // Getters and setters
    Field getField() const;
    void setField(const Field &f);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);

private:
    static const unsigned int field_size;
};

#endif // CHESSLABEL_H