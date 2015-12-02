#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QMainWindow>
#include <QGridLayout>
#include <QMenu>
#include <QLabel>
#include <QList>
#include <QPair>
#include <QString>

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
    void highlightPossibleMove(int row, int col);

private:
    Ui::Chessboard *ui;

    QGridLayout * grid;
    QList<QPair<QLabel*, QString> > squares;

    // Menu bar
    QMenu * fileMenu;

    // Pixel size of square board
    int pixelSizeBoard;
};

#endif // CHESSBOARD_H
