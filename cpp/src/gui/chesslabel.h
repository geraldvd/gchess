#ifndef CHESSLABEL_H
#define CHESSLABEL_H

// Include Qt library
#include <QLabel>

// Include project libraries
#include "../utils.h"
#include "../board/move.h"

/**
 * @brief ChessLabel class inherits from QLabel. Goal: clickable, contains chess field locations
 */
class ChessLabel : public QLabel
{
    Q_OBJECT
public:
    // Constructors
    explicit ChessLabel(QWidget* parent=0);
    explicit ChessLabel(const unsigned int &f, QWidget *parent=0);

    // Getters and setters
    Field getPosition() const;
    void setPosition(const unsigned int &f);
    void setMove(const Move &m);
    bool hasMove() const;
    Move* getMove();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);

private:
    Move pieceMove;
    static const unsigned int field_size;
};

#endif // CHESSLABEL_H
