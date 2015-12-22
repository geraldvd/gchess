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
    board(0),
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
    this->newGame(1);
}

ChessGame::~ChessGame()
{
    delete this->file_menu;
}

void ChessGame::newGame(const int &board_layout)
{
    // Empty board
    this->chessboard->clearPieces();
    this->chessboard->clearHighlights();

    // Start new game
    this->board.initBoard(board_layout);
    this->statusBar()->showMessage(QString::fromStdString(this->board.getActivePlayer()->getColorString()));

    // Add pieces
    for(auto p : this->board.getPieces()) {
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
        if(this->board.getActivePlayer()->getColor() == this->board.getTile(l->getPosition())->getPiece()->getColor()) {
            this->activeField = l;

            // Clear old highlights
            this->chessboard->clearHighlights();

            // Highlight moves
            for(auto &m : this->board.getActivePlayer()->getMoves()) {
                this->chessboard->highlightField(m);
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
    if(this->activeField != NULL && to->hasMove()) {
        Field from = this->activeField->getPosition();
        //MoveType m = this->game.getMoveType(from, to->getPosition());

        switch(to->getMove()->getMoveType()) {
        case MT_PROMOTION:
            {
                PromotionDialog pd(to->getMove()->getMovingPiece()->getColor());
                if(pd.exec()) {
                    // TODO move return bool?
                    this->board.move(from, to->getPosition(), pd.getPromotionType());
                    this->chessboard->removePiece(from.getPosition());
                    this->chessboard->addPiece(to->getPosition().getPosition(), pd.getPieceColor(), pd.getPieceType());
                } else {
                    // Assume queen
                    this->board.move(from, to->getPosition(), PT_QUEEN);
                    this->chessboard->removePiece(from.getPosition());
                    this->chessboard->addPiece(to->getPosition().getPosition(), pd.getPieceColor(), QUEEN);
                }
            }
            break;
        case MT_CASTLING:
            // Move king
            this->board.move(from, to->getPosition());
            this->chessboard->movePiece(from.getPosition(), to->getPosition().getPosition());
            // Move rook
            if(this->board.getTile(to->getPosition())->getX() == 1) {
                this->chessboard->movePiece(to->getPosition().getPosition()-1, to->getPosition().getPosition()+1);
            } else {
                this->chessboard->movePiece(to->getPosition().getPosition()+1, to->getPosition().getPosition()-1);
            }
            break;
        case MT_ENPASSANT:
            this->board.move(from, to->getPosition());
            if(this->board.getTile(to->getPosition())->getPiece()->getColor() == WHITE) {
                this->chessboard->removePiece(to->getPosition().getPosition()-8);
            } else {
                this->chessboard->removePiece(to->getPosition().getPosition()+8);
            }
        case MT_PAWNJUMP:
        case MT_NORMAL:
            this->board.move(from, to->getPosition());
            this->chessboard->movePiece(from.getPosition(), to->getPosition().getPosition());
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
        this->statusBar()->showMessage(QString::fromStdString(this->board.getActivePlayer()->getColorString()));


        // Highlight if king is in check position; Note: only one king can be check - TODO: is this a task for the gui?
        if(this->board.getActivePlayer()->kingCheck()) {
            this->chessboard->checkField(this->board.getActivePlayer()->getKing()->getTile()->getPosition());
        }
    }
}

