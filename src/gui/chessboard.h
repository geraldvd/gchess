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

    void setStatusBar(QString text);

    void highlightPossibleMove(std::pair<int,int> position);
    void highlightPossibleMoves(Piece *p);

    // Piece methods
    void addPiece(std::string type, int color, std::pair<int, int> globalPosition);
    void addPiece(Piece *p);
    void removePiece(std::pair<int,int> position);
    void movePiece(std::pair<int,int> from, std::pair<int,int> to);

private:
    Ui::Chessboard *ui;

    QGridLayout * grid;
    QList<QPair<QLabel*, QString> > squares;
    //TODO do I need the QPair?? Should move be covered by game class?
    //std::map<std::pair<int,int>,QPair<QLabel*,Piece*> > pieces;
    std::map<std::pair<int,int>,QLabel*> pieces;

    // Menu bar
    QMenu * fileMenu;

    // Pixel size of square board
    int pixelSizeBoard;
};

#endif // CHESSBOARD_H
