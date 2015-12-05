#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QMainWindow>
#include <QGridLayout>
#include <QMenu>
#include <QLabel>
#include <QList>
#include <QPair>
#include <QString>

#include <utility>
#include <map>

#include "game.h"

namespace Ui {
class Chessboard;
}

class Chessboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Chessboard(QWidget *parent = 0);
    ~Chessboard();
    void newGame();

    void setStatusBar(QString text);

    void highlightField(Field position);
    void highlightPossibleMoves(Piece *p);

    // Piece methods
    void addPiece(Piece *p);
    void removePiece(Field position);
    void movePiece(Field from, Field to);

private:
    // UI elements
    Ui::Chessboard *ui;
    QGridLayout * grid;
    QList<QPair<QLabel*, QString> > squares;
    //TODO do I need the QPair?? Should move be covered by game class?
    std::map<std::pair<int,int>,QLabel*> pieces;
    QMenu * fileMenu;

    // Pixel size of square board
    int pixelSizeBoard;

    // Game variables
    Game game;
};

#endif // CHESSBOARD_H
