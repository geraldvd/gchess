#include "chessboard.h"
#include "ui_chessboard.h"

Chessboard::Chessboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Chessboard)
{
    ui->setupUi(this);
}

Chessboard::~Chessboard()
{
    delete ui;
}
