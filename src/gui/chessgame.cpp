#include "chessgame.h"
#include "promotiondialog.h"

#include <QDebug>

ChessGame::ChessGame(QWidget *parent) :
    QMainWindow(parent),

    // Initialize widgets
    chessboard(new Chessboard(this)),

    // Initialize menu's
    file_menu(new QMenu("file")),

    // Initialize game
    game(Game()),
    activeField(NULL)
{

    // Setup window parameters
    this->setWindowTitle("Chess");
    this->setFixedWidth(this->chessboard->width());
    this->setFixedHeight(this->chessboard->height() + this->statusBar()->height() + this->menuBar()->height());

    // Setup layout
    this->setCentralWidget(this->chessboard);

    // Setup menubar
    QList<QAction *> actions;
    actions.append(new QAction("New Game", this->file_menu));
    actions.append(new QAction("Exit", this->file_menu));

    // Add menu's
    this->file_menu = this->menuBar()->addMenu("&File");
    this->file_menu->addActions(actions);

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

//void ChessGame::addPiece(Piece *p)
//{
//    this->pieces[p->getPosition()] = p;
//    this->chessboard->addPiece(p->getPosition(), p->getColor(), p->getType());
//}

void ChessGame::newGame()
{
    // Empty board
    this->chessboard->clearPieces();
    this->chessboard->clearHighlights();

    // Start new game
    this->game.newGame();
    this->statusBar()->showMessage(QString::fromStdString(this->game.getActivePlayerString()));

    // Add pieces
    for(auto p : this->game.getBoard()->getPieces()) {
        this->chessboard->addPiece(p->getTile()->getPosition(), p->getColor(), p->getType());
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
        if(this->game.getActivePlayer() == this->game.getBoard()->getTile(l->getPosition())->getPiece()->getColor()) {
            this->activeField = l;

            // Clear old highlights
            this->chessboard->clearHighlights();

            // Highlight moves
            for(auto &i : this->game.getPositionsPossibleMoves(l->getPosition())) {
                this->chessboard->highlightField(i);
            }
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
        unsigned int from = this->activeField->getPosition();
        enum MoveType m = this->game.getMoveType(from, to->getPosition());

        switch(m) {
        case MT_PROMOTION:
            {
                PromotionDialog pd(this->game.getBoard()->getTile(from)->getPiece()->getColor());
                if(pd.exec()) {
                    this->game.move(from, to->getPosition(), pd.getPromotionType());
                    this->chessboard->removePiece(from);
                    this->chessboard->addPiece(to->getPosition(), pd.getPieceColor(), pd.getPieceType());
                } else {
                    // Assume queen
                    this->game.move(from, to->getPosition(), PT_QUEEN);
                    this->chessboard->removePiece(from);
                    this->chessboard->addPiece(to->getPosition(), pd.getPieceColor(), QUEEN);
                }
            }
            break;
        case MT_CASTLING:
            // Move king
            this->game.move(from, to->getPosition());
            this->chessboard->movePiece(from, to->getPosition());
            // Move rook
            if(this->game.getBoard()->getTile(to->getPosition())->getX() == 1) {
                this->chessboard->movePiece(to->getPosition()-1, to->getPosition()+1);
            } else {
                this->chessboard->movePiece(to->getPosition()+1, to->getPosition()-1);
            }
            break;
        case MT_ENPASSANT:
            this->game.move(from, to->getPosition());
            if(this->game.getBoard()->getTile(to->getPosition())->getPiece()->getColor() == WHITE) {
                this->chessboard->removePiece(to->getPosition()-8);
            } else {
                this->chessboard->removePiece(to->getPosition()+8);
            }
        case MT_PAWNJUMP:
        case MT_NORMAL:
            this->game.move(from, to->getPosition());
            this->chessboard->movePiece(from, to->getPosition());
            break;
        case MT_INVALID:
            // Do nothing
            return;
        }

        // Unhighlight all fields
        this->activeField = NULL;
        this->chessboard->clearHighlights();

        // Unhighlight check position
        this->chessboard->unCheckField();

        // Set new active player
        this->statusBar()->showMessage(QString::fromStdString(this->game.getActivePlayerString()));


        // Highlight if king is in check position; Note: only one king can be check - TODO: is this a task for the gui?
        for(auto &p : this->game.getBoard()->getPieces()) {
            if(p->getType() == KING && p->getTile()->tileUnderAttack(this->game.getBoard(), this->game.getActivePlayer())) {
                this->chessboard->checkField(p->getTile()->getPosition());
                break;
            }
        }
    }
}

