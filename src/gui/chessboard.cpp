#include "chessboard.h"
#include "ui_chessboard.h"

#include <QPainter>
#include <QAction>

using namespace std;


Chessboard::Chessboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Chessboard),
    grid(new QGridLayout),

    fileMenu(new QMenu("File")),

    pixelSizeBoard(800)
{
    ui->setupUi(this);

    // Setup main window
    this->setWindowTitle("Chessboard");
    this->setFixedHeight(this->pixelSizeBoard + this->ui->menubar->height() + this->ui->statusBar->height());
    this->setFixedWidth(this->pixelSizeBoard);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // Setup grid
    this->grid->setSpacing(0);
    this->grid->setMargin(0);
    this->grid->setContentsMargins(0,0,0,0);

    // Setup menubar
    QList<QAction *> actions;
    actions.append(new QAction("Exit", this->fileMenu));
    this->fileMenu->addActions(actions);
    this->menuBar()->addMenu(this->fileMenu);

    // Setup square locations
    char lastColor = 1;
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            // Create a label
            auto l = new QLabel(ui->centralwidget);

            // Specify label color
            QString currentColor{"white"};
            if(lastColor < 0) {
                currentColor = "#a36629";
            }
            l->setStyleSheet("background-color: " + currentColor);
            lastColor *= -1;

            // Specify label size
            l->setFixedHeight(this->pixelSizeBoard / 8);
            l->setFixedWidth(this->pixelSizeBoard / 8);

            // Add label to grid
            this->squares.append(QPair<QLabel*, QString>(l, currentColor));
            grid->addWidget(l, i, j,  Qt::AlignTop);
        }
        lastColor *= -1;
    }
    ui->centralwidget->setLayout(grid);
}

Chessboard::~Chessboard()
{
    delete this->ui;
    delete this->grid;

    delete this->fileMenu;
}

void Chessboard::setStatusBar(QString text)
{
    this->ui->statusBar->showMessage(text);
}

void Chessboard::highlightPossibleMove(int row, int col)
{
    QPair<QLabel*,QString> l{this->squares[8*col + row]};
    int radius = 10;

    QPixmap pm(l.first->width(),l.first->height());

    QPainter p(&pm);
    p.fillRect(pm.rect(), QColor(l.second));
    p.setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::lightGray, 0);
    p.setPen(pen);
    QBrush brush("#cccccc");
    p.setBrush(brush);
    p.drawEllipse(l.first->width()/2-radius,l.first->height()/2-radius,2*radius,2*radius);
    l.first->setPixmap(pm);
}
