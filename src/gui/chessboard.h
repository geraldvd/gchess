#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QMainWindow>

namespace Ui {
class Chessboard;
}

class Chessboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Chessboard(QWidget *parent = 0);
    ~Chessboard();

private:
    Ui::Chessboard *ui;
};

#endif // CHESSBOARD_H
