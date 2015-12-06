#include "chessboard.h"
#include "ui_chessboard.h"

#include <QPainter>
#include <QAction>
#include <QDebug>
#include <QBitmap>

using namespace std;

const int Chessboard::pixelSizeBoard = 400;


Chessboard::Chessboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Chessboard),
    grid(new QGridLayout),

    fileMenu(new QMenu("File")),

    pieceWithHighlightedMoves(NULL)
{
    ui->setupUi(this);

    // Setup main window
    this->setWindowTitle("Chessboard");
    this->setFixedHeight(Chessboard::pixelSizeBoard + this->ui->menubar->height() + this->ui->statusBar->height());
    this->setFixedWidth(Chessboard::pixelSizeBoard);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // Setup menubar
    QList<QAction *> actions;
    actions.append(new QAction("New Game", this->fileMenu));
    actions.append(new QAction("Exit", this->fileMenu));
    // Add menu's
    this->fileMenu->addActions(actions);
    this->menuBar()->addMenu(this->fileMenu);
    // Setup menu signals and slots
    connect(this->fileMenu->actions().at(0), SIGNAL(triggered()), this, SLOT(newGame()));
    connect(this->fileMenu->actions().at(1), SIGNAL(triggered()), this, SLOT(close()));

    // Setup board (empty fields and empty pieces)
    this->initBoard();

    // Start new chess game
    this->newGame();
}

Chessboard::~Chessboard()
{
    // Release memory gui
    delete this->ui;
    delete this->grid;
    delete this->fileMenu;

    // Release other memory
    // (Don't delete pieceWithHighlightedMoves; will be done in game class)
    // TODO must pieces map be deleted?

}

void Chessboard::initBoard()
{
    // Empty existing variables
    this->squares = map<Field,PieceLabel*>();
    this->pieces = map<Field,PieceLabel*>();
    this->pieceWithHighlightedMoves = NULL;
    this->possibleMoves = vector<Field>();

    // Setup grid
    this->grid->setSpacing(0);
    this->grid->setMargin(0);
    this->grid->setContentsMargins(0,0,0,0);

    // Setup square locations
    char lastColor = 1;
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            /* Create square */
            // Create a label
            auto sl = new PieceLabel(ui->centralwidget);

            // Specify label color
            QString currentColor{"white"};
            if(lastColor < 0) {
                currentColor = "#a36629";
            }
            sl->setStyleSheet("background-color: " + currentColor);
            sl->setSquareColor(currentColor);
            lastColor *= -1;

            // Specify label size
            sl->setFixedHeight(Chessboard::pixelSizeBoard / 8);
            sl->setFixedWidth(Chessboard::pixelSizeBoard / 8);


            // Add label to grid
            this->squares.insert(pair<Field,PieceLabel*>(Field(i,7-j), sl));
            grid->addWidget(sl, j, i,  Qt::AlignTop);

            /* Create piece holder */
            auto pl = new PieceLabel(sl);
            QPixmap pm("/home/gerald/git/gchess/src/gui/king_black.png");
            pl->setPixmap(pm);
            pl->setMask(pm.mask());
            this->pieces.insert(pair<Field,PieceLabel*>(Field(i, 7-j), pl));

            // Connect signal to slot for moving pieces
            connect(pl, SIGNAL(clicked()),this, SLOT(movePieceSlot()));
            connect(sl, SIGNAL(clicked()),this, SLOT(movePieceSlot()));
        }
        lastColor *= -1;
    }
    ui->centralwidget->setLayout(grid);
}

void Chessboard::clearPieces() {
    for(auto &p : this->pieces) {
        auto pl = p.second;
        QPixmap pm;
        pl->setPixmap(pm);
        pl->setMask(pm.mask());
    }
}

void Chessboard::newGame()
{
    // Reset variables
    this->clearPieces();
    this->game = Game();
    this->pieceWithHighlightedMoves = NULL;
    this->possibleMoves = vector<Field>();

    // Start new game
    this->game = Game();
    this->game.init();
    this->ui->statusBar->showMessage(QString::fromStdString(this->game.getActivePlayerString()));

    // Place pieces
    for(auto &p : this->game.getPieces()) {
        this->addPiece(p);
    }

    qDebug() << "New game started!" << endl;
}

void Chessboard::drawCircleOnField(const Field & position)
{
    // Determine location of highlight
    PieceLabel* l{this->squares[position]};

    // Draw circle for highlighting
    int radius = 10;
    QPixmap pm(l->width(),l->height());
    QPainter p(&pm);
    p.fillRect(pm.rect(), QColor(l->getSquareColor()));
    p.setRenderHint(QPainter::Antialiasing, true);
    // Pen settings
    QPen pen(Qt::lightGray, 0);
    p.setPen(pen);
    // Brush settings
    QBrush brush("#cccccc");
    p.setBrush(brush);
    // Draw circle
    p.drawEllipse(l->width()/2-radius, l->height()/2-radius, 2*radius, 2*radius);
    l->setPixmap(pm);
}

void Chessboard::removeCircleFromField(const Field & position)
{
    // Determine location to un-highlight
    PieceLabel* l{this->squares[position]};

    // Add empty pixmap to field
    QPixmap pm(l->width(), l->height());
    QPainter p(&pm);
    p.fillRect(pm.rect(), QColor(l->getSquareColor()));
    l->setPixmap(pm);
}


void Chessboard::highlightPossibleMoves(Piece *p)
{
    // Unhighlight already highlighted fields
    if(this->pieceWithHighlightedMoves == p) {
        // Un-highlight moves and return
        vector<Field> moves = p->getMoves();
        for(auto &m : moves) {
            this->removeCircleFromField(m);
        }
        this->pieceWithHighlightedMoves = NULL;
        this->possibleMoves = vector<Field>();
        return;
    } else if(this->pieceWithHighlightedMoves != NULL) {
        // Un-highlight moves and do not return
        vector<Field> moves = this->pieceWithHighlightedMoves->getMoves();
        for(auto &m : moves) {
            this->removeCircleFromField(m);
        }
        this->pieceWithHighlightedMoves = NULL;
        this->possibleMoves = vector<Field>();
    }
    if(p->getColor() == this->game.getActivePlayer()) {
        // Highlight moves
        vector<Field> moves = p->getMoves();
        for(auto &m : moves) {
            this->drawCircleOnField(m);
            this->possibleMoves.push_back(m);
        }

        this->pieceWithHighlightedMoves = p;
        qDebug() << "Number of moves (" << QString::fromStdString(p->getPositionString()) << "): " << moves.size() << endl;
    }

}

void Chessboard::unhighlightPossibleMoves() {
    for(auto &m : this->possibleMoves) {
        this->removeCircleFromField(m);
    }
}

void Chessboard::addPiece(Piece* p)
{    
    // Determine image file name
    QString filename;
    if(p->getType() == "King") {
        if(p->getColor() == WHITE) {
            filename = "king_white.png";
        } else {
            filename = "king_black.png";
        }
    } else if(p->getType() == "Queen") {
        if(p->getColor() == WHITE) {
            filename = "queen_white.png";
        } else {
            filename = "queen_black.png";
        }
    } else if(p->getType() == "Rook") {
        if(p->getColor() == WHITE) {
            filename = "rook_white.png";
        } else {
            filename = "rook_black.png";
        }
    } else if(p->getType() == "Knight") {
        if(p->getColor() == WHITE) {
            filename = "knight_white.png";
        } else {
            filename = "knight_black.png";
        }
    } else if(p->getType() == "Bishop") {
        if(p->getColor() == WHITE) {
            filename = "bishop_white.png";
        } else {
            filename = "bishop_black.png";
        }
    } else if(p->getType() == "Pawn") {
        if(p->getColor() == WHITE) {
            filename = "pawn_white.png";
        } else {
            filename = "pawn_black.png";
        }
    }

    // Draw piece
    QPixmap pm("/home/gerald/git/gchess/src/gui/"+filename);
    //PieceLabel *lb = new PieceLabel(p, this->squares[p->getPosition()]);
    auto lb = this->pieces[p->getPosition()];
    lb->setPiece(p);
    lb->setPixmap(pm);
    lb->setMask(pm.mask());

    // Test signals/slots
    connect(lb, SIGNAL(clicked()), this, SLOT(toggleHighlightMoves()));
}

void Chessboard::removePiece(const Field &position)
{
    PieceLabel *lb = this->pieces[position];

    // Remove piece
    lb->setPiece(NULL);
    QPixmap pm;
    lb->setPixmap(pm);
    lb->setMask(pm.mask());
}

void Chessboard::movePiece(const Field & from, const Field & to)
{
    this->removePiece(from);
    this->addPiece(this->pieceWithHighlightedMoves);

    //PieceLabel *lb = this->pieces[from];
    //lb->setParent(this->squares[to]);

    //QPixmap pm("/home/gerald/git/gchess/src/gui/king_black.png");
    //lb->setPixmap(pm);
    //lb->setMask(pm.mask());

    //lb->move(x,y);
}

void Chessboard::movePiece(Piece *p, const Field & from)
{
    // Remove old piece
    this->removePiece(from);

    // Redraw piece
    this->addPiece(p);
}

void Chessboard::toggleHighlightMoves()
{
    PieceLabel* lb = dynamic_cast<PieceLabel*>(sender());
    this->highlightPossibleMoves(lb->getPiece());
}

void Chessboard::movePieceSlot()
{
    // Specify originating field
    PieceLabel* lb = dynamic_cast<PieceLabel*>(sender());

    // Check whether square is populated
    if(this->pieceWithHighlightedMoves != NULL) {
        // Store data before move
        Field from(this->pieceWithHighlightedMoves->getPosition());

        // Move piece
        if(this->game.move(this->pieceWithHighlightedMoves, lb->getField())) {
            // Move is allowed!
            qDebug() << "Move allowed!" << endl;
            this->movePiece(from, this->pieceWithHighlightedMoves->getPosition());
qDebug() << this->pieces.size() << endl;
            // Set new active player
            this->ui->statusBar->showMessage(QString::fromStdString(this->game.getActivePlayerString()));
        }

        // Remove move highlighting
        this->unhighlightPossibleMoves();
    }
}
