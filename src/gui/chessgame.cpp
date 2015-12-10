#include "chessgame.h"

ChessGame::ChessGame(QWidget *parent) :
    menubar(new QMenuBar(this)),
    chessboard(new Chessboard2(this)),
    statusbar(new QStatusBar(this)),

    file_menu(new QMenu("file")),

    game(Game())
{
    // Setup window parameters
    this->setWindowTitle("Chess");
    this->setFixedWidth(this->chessboard->width());
    this->setFixedHeight(this->chessboard->height() + this->menubar->height() + this->statusbar->height());

    // Setup menubar
    QList<QAction *> actions;
    actions.append(new QAction("New Game", this->file_menu));
    actions.append(new QAction("Exit", this->file_menu));

    // Add menu's
    this->file_menu->addActions(actions);
    this->menuBar()->addMenu(this->file_menu);

    // Setup menu signals and slots
    connect(this->file_menu->actions().at(0), SIGNAL(triggered()), this, SLOT(newGame()));
    connect(this->file_menu->actions().at(1), SIGNAL(triggered()), this, SLOT(close()));

    // Start new game
    this->newGame();
}

ChessGame::~ChessGame()
{
    delete this->file_menu;
}

void ChessGame::newGame()
{
    // TODO does not work yet when used via menu!


    // Empty board
    //this->chessboard->clearPieces();
    this->chessboard->clearHighlights();

    // Start new game
    this->game.init();
    this->statusbar->showMessage(QString::fromStdString(this->game.getActivePlayerString()));

    // Place pieces TODO: other interface? (more generic)
    for(auto p : this->game.getPieces()) {
        this->chessboard->addPiece(p->getPosition(), p->getColor(), p->getType());
    }
}

