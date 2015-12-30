// Include Qt libraries
#include <QDebug>

// Include project files
#include "chessgame.h"
#include "promotiondialog.h"
#include "../piece/king.h"


ChessGame::ChessGame(QWidget *parent) :
    QMainWindow(parent),

    // Initialize widgets
    chessboard(new Chessboard(this)),

    // Initialize menu's
    game_menu(new QMenu("file")),

    // Initialize game
    game(),
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
    actions.append(new QAction("New Game", this->game_menu));
    actions.append(new QAction("Test: Promotion", this->game_menu));
    actions.append(new QAction("Test: Castling", this->game_menu));
    actions.append(new QAction("Test: Move into check", this->game_menu));
    actions.append(new QAction("Test: Move out check (1)", this->game_menu));
    actions.append(new QAction("Test: Move out check (2)", this->game_menu));
    actions.append(new QAction("Exit", this->game_menu));

    // Add menu's
    this->game_menu = this->menuBar()->addMenu("&Game");
    this->game_menu->addActions(actions);

    // Setup menu signals and slots
    connect(this->game_menu->actions().at(0), SIGNAL(triggered()), this, SLOT(newGame()));
    connect(this->game_menu->actions().at(1), SIGNAL(triggered()), this, SLOT(promotionTest()));
    connect(this->game_menu->actions().at(2), SIGNAL(triggered()), this, SLOT(castlingTest()));
    connect(this->game_menu->actions().at(3), SIGNAL(triggered()), this, SLOT(moveIntoCheckTest()));
    connect(this->game_menu->actions().at(4), SIGNAL(triggered()), this, SLOT(moveOutOfCheckTest()));
    connect(this->game_menu->actions().at(5), SIGNAL(triggered()), this, SLOT(moveOutOfCheckTest2()));
    connect(this->game_menu->actions().at(6), SIGNAL(triggered()), this, SLOT(close()));

    // Start new game
    this->newGame(0);
}

ChessGame::~ChessGame()
{
    delete this->game_menu;
}

void ChessGame::newGame(const int &board_layout)
{
    // Empty board
    this->chessboard->clearPieces();
    this->chessboard->clearHighlights();
    this->chessboard->unCheckField();

    // Start new game
    this->game.initBoard(board_layout);
    this->statusBar()->showMessage(this->getStatusMessage());

    // Add pieces
    for(auto p : this->game.getBoard()->getPieces()) {
        this->chessboard->addPiece(p->getTile()->getPosition(), p->getColor(), p->getType());
    }
}

void ChessGame::promotionTest()
{
    this->newGame(1);
}

void ChessGame::castlingTest()
{
    this->newGame(2);
}

void ChessGame::moveIntoCheckTest()
{
    this->newGame(3);
}

void ChessGame::moveOutOfCheckTest()
{
    this->newGame(4);
}

void ChessGame::moveOutOfCheckTest2()
{
    this->newGame(5);
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
        if(this->game.getBoard()->getActivePlayer() == this->game.getBoard()->getTile(l->getPosition())->getPiece()->getColor()) {
            this->activeField = l;

            // Clear old highlights
            this->chessboard->clearHighlights();

            // Highlight moves
            for(auto &m : this->game.getBoard()->getMoves(this->game.getBoard()->getActivePlayer())) {
                // Only highlight moves of clicked piece
                if(*m.getMovingPiece()->getTile() == l->getPosition()) {
                    this->chessboard->highlightField(m);
                }
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

        switch(to->getMove()->getMoveType()) {
        case MT_PROMOTION:
            {
                PromotionDialog pd(to->getMove()->getMovingPiece()->getColor());
                if(pd.exec()) {
                    // TODO move return bool?
                    to->getMove()->setPromotionType(pd.getPromotionType());
                    if(this->game.move(from, to->getMove()->getDestination()) == MS_OK) {
                        this->chessboard->removePiece(from.getPosition());
                        this->chessboard->addPiece(to->getPosition().getPosition(), pd.getPieceColor(), pd.getPieceType());
                    }
                } else {
                    // Assume queen
                    to->getMove()->setPromotionType(PT_QUEEN);
                    if(this->game.move(from, to->getMove()->getDestination()) == MS_OK) {
                        this->chessboard->removePiece(from.getPosition());
                        this->chessboard->addPiece(to->getPosition().getPosition(), pd.getPieceColor(), QUEEN);
                    }
                }
            }
            break;
        case MT_CASTLING:
            if(this->game.move(from, to->getMove()->getDestination()) == MS_OK) {
                // Move king
                this->chessboard->movePiece(from.getPosition(), to->getPosition().getPosition());
                // Move rook
                if(this->game.getBoard()->getTile(to->getPosition())->getX() == 2) {
                    this->chessboard->movePiece(to->getPosition().getPosition()-2, to->getPosition().getPosition()+1);
                } else {
                    this->chessboard->movePiece(to->getPosition().getPosition()+1, to->getPosition().getPosition()-1);
                }
            }
            break;
        case MT_ENPASSANT:
            if(this->game.move(from, to->getMove()->getDestination()) == MS_OK) {
                if(this->game.getBoard()->getTile(to->getPosition())->getPiece()->getColor() == WHITE) {
                    this->chessboard->removePiece(to->getPosition().getPosition()-8);
                } else {
                    this->chessboard->removePiece(to->getPosition().getPosition()+8);
                }
                this->chessboard->movePiece(from.getPosition(), to->getPosition().getPosition());
            }
            break;
        case MT_PAWNJUMP:
        case MT_NORMAL:
            if(this->game.move(from, to->getMove()->getDestination()) == MS_OK) {
                this->chessboard->movePiece(from.getPosition(), to->getPosition().getPosition());
            }
            break;
        case MT_NONE:
            // Do nothing
            return;
        }

        // Unhighlight all fields
        this->activeField = NULL;
        this->chessboard->clearHighlights();

        // Unhighlight check position
        this->chessboard->unCheckField();

        // Set new active player
        this->statusBar()->showMessage(this->getStatusMessage());


        // Highlight if king is in check position; Note: only one king can be check - TODO: is this a task for the gui?
//        if(this->game.getActivePlayer().kingCheck()) {
//            this->chessboard->checkField(this->game.getActivePlayer().getKing()->getTile()->getPosition());
//        }
    }
}

QString ChessGame::getStatusMessage()
{
    return QString::fromStdString(this->game.getBoard()->getActivePlayerString() +
                                  " (Board status: " + this->game.getBoard()->getBoardStatusString() + ")");
}

