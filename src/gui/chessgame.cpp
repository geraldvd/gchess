#include "chessgame.h"

ChessGame::ChessGame(QWidget *parent) :
    menubar(new QMenuBar(this)),
    chessboard(new Chessboard2(this)),
    statusbar(new QStatusBar(this)),

    file_menu(new QMenu("file")),

    game(Game()),
    activeField(NULL)
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

void ChessGame::addPiece(Piece *p)
{
    this->pieces[p->getPosition()] = p;
    this->chessboard->addPiece(p->getPosition(), p->getColor(), p->getType());
}

void ChessGame::highlightMoves(Piece *p)
{
    this->chessboard->clearHighlights();
    for(auto &m : p->getMoves()) {
        this->chessboard->highlightField(m);
    }
}

void ChessGame::newGame()
{
    // Empty board
    this->chessboard->clearPieces();
    this->chessboard->clearHighlights();

    // Start new game
    this->game.init();
    this->statusbar->showMessage(QString::fromStdString(this->game.getActivePlayerString()));

    // Place pieces TODO: other interface? (more generic)
    for(auto p : this->game.getPieces()) {
        this->addPiece(p);
    }
}

void ChessGame::toggleHighlighting()
{
    // Obtain piece to be toggled
    ChessLabel* l = dynamic_cast<ChessLabel*>(sender());

    // Check whether already highlighted and toggle
    if(l == this->activeField) {
        this->chessboard->clearHighlights();
        this->activeField = NULL;
    } else {
        // Check whether piece is allowed to move
        if(this->game.getActivePlayer() == this->pieces[l->getField()]->getColor()) {
            this->activeField = l;
            this->highlightMoves(this->pieces[l->getField()]);
        } else {
            this->chessboard->clearHighlights();
            this->activeField = NULL;
        }
    }
}

void ChessGame::slotMovePiece()
{
    // Obtain destination for move
    ChessLabel* to = dynamic_cast<ChessLabel*>(sender());

    // Move piece if allowed
    if(this->activeField != NULL) {
        Field from = this->activeField->getField();

        if(this->game.move(this->pieces[this->activeField->getField()], to->getField())) {
            this->chessboard->movePiece(this->activeField->getField(), to->getField());

            // Update piece positions (in this class)
            this->pieces[to->getField()] = this->pieces[from];
            this->pieces.erase(from);

            // Unhighlight all fields
            this->activeField = NULL;
            this->chessboard->clearHighlights();

            // Set new active player
            this->statusbar->showMessage(QString::fromStdString(this->game.getActivePlayerString()));
        }
    }


}

