#include "chessboard.h"
#include "ui_chessboard.h"

#include <QPainter>
#include <QAction>
#include <QDebug>
#include <QBitmap>


using namespace std;


Chessboard::Chessboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Chessboard),
    grid(new QGridLayout),

    fileMenu(new QMenu("File")),

    pixelSizeBoard(400)
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

            // Test
            QPixmap pm("/home/gerald/git/gchess/src/gui/king_black_icon.png");
            QLabel *lb = new QLabel(l);
            lb->setPixmap(pm);
            lb->setMask(pm.mask());
            lb->setAlignment(Qt::AlignCenter);
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

void Chessboard::highlightPossibleMove(std::pair<int, int> position)
{
    QPair<QLabel*,QString> l{this->squares[8*(7-position.second) + position.first]};
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

void Chessboard::highlightPossibleMoves(Piece *p)
{
    vector<pair<int,int> > moves = p->getGlobalMoves();

    for(auto &m : moves) {
        this->highlightPossibleMove(m);
    }

    qDebug() << "Number of moves (" << QString::fromStdString(p->getLetterPosition()) << "): " << moves.size() << endl;
}

void Chessboard::addPiece(string type, int color, pair<int,int> globalPosition)
{
    // Determine image file name
    QString filename;
    if(type == "King") {
        if(color > 0) {
            filename = "king_white.png";
        } else {
            filename = "king_black.png";
        }
    } else if(type == "Queen") {
        if(color > 0) {
            filename = "queen_white.png";
        } else {
            filename = "queen_black.png";
        }
    } else if(type == "Rook") {
        if(color > 0) {
            filename = "rook_white.png";
        } else {
            filename = "rook_black.png";
        }
    } else if(type == "Knight") {
        if(color > 0) {
            filename = "knight_white.png";
        } else {
            filename = "knight_black.png";
        }
    } else if(type == "Bishop") {
        if(color > 0) {
            filename = "bishop_white.png";
        } else {
            filename = "bishop_black.png";
        }
    } else if(type == "Pawn") {
        if(color > 0) {
            filename = "pawn_white.png";
        } else {
            filename = "pawn_black.png";
        }
    }

    // Convert chess coordinate system to qt coordinate system
    int x = globalPosition.first;
    int y = 7 - globalPosition.second;

    // Draw piece
    QPixmap pm("/home/gerald/git/gchess/src/gui/"+filename);
    QLabel *lb = new QLabel(this->squares.at(8*y + x).first);
    lb->setPixmap(pm);
    lb->setMask(pm.mask());

    // Add piece to list
    //this->pieces[globalPosition] = QPair<QLabel*,Piece*>(lb, p);
    this->pieces[globalPosition] = lb;
}

void Chessboard::addPiece(Piece *p)
{
    this->addPiece(p->getType(), p->getColor(), p->getGlobalPosition());
}

void Chessboard::removePiece(std::pair<int, int> position)
{
    QLabel *lb = this->pieces[position];
    delete lb;

    this->pieces.erase(position);
}

void Chessboard::movePiece(std::pair<int, int> from, std::pair<int, int> to)
{
    int x = to.first;
    int y = 7 - to.second;

    QLabel *lb = this->pieces[from];
    lb->setParent(this->squares.at(8*y + x).first);
}
