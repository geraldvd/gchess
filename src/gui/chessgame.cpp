// Include Qt libraries
#include <QDebug>

// Include project files
#include "chessgame.h"
#include "promotiondialog.h"
#include "../piece/king.h"


ChessGame::ChessGame(QWidget *parent) :
    QMainWindow(parent),

    // Initialize widgets
    container(new QWidget(this)),
    chessboard(new Chessboard(this)),
    moveHistoryBox(new QGroupBox("Move history", this)),
    moveHistory(new QListWidget(this->moveHistoryBox)),
    revertMoveButton(new QPushButton("Revert move", this->moveHistoryBox)),

    // Initialize menu's
    game_menu(new QMenu("file")),

    // Initialize game
    game(),
    activeField(NULL),
    boardActive(false)
{

    // Setup window parameters
    this->setWindowTitle("Chess");
    //this->setFixedWidth(this->chessboard->width());
    //this->setFixedHeight(this->chessboard->height() + this->statusBar()->height() + this->menuBar()->height());

    // Layout move history box
    this->moveHistoryBox->setFlat(true);
    QLayout *vertical = new QVBoxLayout(this->moveHistoryBox);
    vertical->addWidget(this->moveHistory);
    vertical->addWidget(this->revertMoveButton);
    // Overall layout
    QLayout *horizontal = new QHBoxLayout(this->container);
    horizontal->addWidget(this->chessboard);
    horizontal->addWidget(this->moveHistoryBox);
    this->setCentralWidget(this->container);

    // Setup menubar
    QList<QAction *> actions;
    actions.append(new QAction("New Game", this->game_menu));
    actions.append(new QAction("Test: Promotion", this->game_menu));
    actions.append(new QAction("Test: rCastling", this->game_menu));
    actions.append(new QAction("Test: Move into check", this->game_menu));
    actions.append(new QAction("Test: Move out check", this->game_menu));
    actions.append(new QAction("Test: En Passent", this->game_menu));
    actions.append(new QAction("Test: Stalemate", this->game_menu));
    actions.append(new QAction("Exit", this->game_menu));

    // Add menu's
    this->game_menu = this->menuBar()->addMenu("&Game");
    this->game_menu->addActions(actions);

    // Mac OS trick (non-native menubar)
    this->menuBar()->setNativeMenuBar(false);

    // Setup menu signals and slots
    connect(this->game_menu->actions().at(0), SIGNAL(triggered()), this, SLOT(newGame()));
    connect(this->game_menu->actions().at(1), SIGNAL(triggered()), this, SLOT(promotionTest()));
    connect(this->game_menu->actions().at(2), SIGNAL(triggered()), this, SLOT(castlingTest()));
    connect(this->game_menu->actions().at(3), SIGNAL(triggered()), this, SLOT(moveIntoCheckTest()));
    connect(this->game_menu->actions().at(4), SIGNAL(triggered()), this, SLOT(moveOutOfCheckTest()));
    connect(this->game_menu->actions().at(5), SIGNAL(triggered()), this, SLOT(enPassantTest()));
    connect(this->game_menu->actions().at(6), SIGNAL(triggered()), this, SLOT(staleMateTest()));
    connect(this->game_menu->actions().at(7), SIGNAL(triggered()), this, SLOT(close()));

    // Setup signals and slots revert move
    connect(this->revertMoveButton, SIGNAL(pressed()), this, SLOT(revertMove()));

    // Start new game
    this->newGame(0);
}

ChessGame::~ChessGame()
{
    delete this->game_menu;
}

void ChessGame::drawBoard(Board *b)
{
    // Empty board
    this->chessboard->clearPieces();
    this->chessboard->unCheckField();
    this->chessboard->clearHighlights();

    // Draw pieces
    for(auto &p : b->getPieces()) {
        this->chessboard->addPiece(p->getTile()->getPosition(), p->getColor(), p->getType());
    }

    // Draw board status
    this->statusBar()->showMessage(this->getStatusMessage(b));

    // Highlight if king is in check position
    if(b->activeKingCheck()) {
        this->chessboard->checkField(b->getActiveKing()->getTile()->getPosition());
    }
}

void ChessGame::newGame(const int &board_layout)
{
    // Start new game
    this->game.initBoard(board_layout);

    // Draw board
    this->drawBoard(this->game.getBoard());
    this->boardActive = true;
    this->updateMoveHistory();
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

void ChessGame::staleMateTest()
{
    this->newGame(6);
}

void ChessGame::enPassantTest()
{
    this->newGame(5);
}

void ChessGame::toggleHighlighting()
{
    // Only do this if board is active (i.e., current)
    if(this->boardActive) {
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
                for(auto &m : this->game.getBoard()->getMoves()) {
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
}

void ChessGame::slotMovePiece()
{
    // Only do this if board is active (i.e., current)
    if(this->boardActive) {
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
                        if(this->game.move(from, to->getMove()->getDestination(), pd.getPromotionType()) == MS_OK) {
                            this->chessboard->removePiece(from.getPosition());
                            this->chessboard->addPiece(to->getPosition().getPosition(), pd.getPieceColor(), pd.getPieceType());
                        }
                    } else {
                        // Assume queen
                        to->getMove()->setPromotionType(PT_QUEEN);
                        if(this->game.move(from, to->getMove()->getDestination(), PT_QUEEN) == MS_OK) {
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
            this->statusBar()->showMessage(this->getStatusMessage(this->game.getBoard()));


            // Highlight if king is in check position; Note: only one king can be check - TODO: is this a task for the gui?
            if(this->game.getBoard()->activeKingCheck()) {
                this->chessboard->checkField(this->game.getBoard()->getActiveKing()->getTile()->getPosition());
            }

            // Update move history pane
            this->updateMoveHistory();
        }
    }
}

void ChessGame::updateMoveHistory() {
    this->moveHistory->clear();

    for(auto &mh : this->game.getMoveHistory()) {
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(mh.first.getMoveString()));
        item->setToolTip(QString::fromStdString(mh.second));
        this->moveHistory->addItem(item);
    }

    // Add current board
    QListWidgetItem *item = new QListWidgetItem("- current -");
    item->setToolTip(QString::fromStdString(this->game.getBoard()->get()));
    this->moveHistory->addItem(item);

    connect(this->moveHistory, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(drawBoardSlot(QListWidgetItem*)));
    emit this->moveHistory->itemClicked(item);
}

void ChessGame::drawBoardSlot(QListWidgetItem *i)
{
    Board b(i->toolTip().toStdString());
    this->drawBoard(&b);

    // Board only active when it is the final board
    if(b.get() == this->game.getBoard()->get()) {
        this->boardActive = true;
    } else {
        this->boardActive = false;
    }
}

void ChessGame::revertMove()
{
    if(this->moveHistory->selectedItems().size() > 0 && this->moveHistory->selectedItems().at(0)->text() != "- current -") {
        // Revert move
        if(this->game.revertMove(this->moveHistory->selectedItems().at(0)->toolTip().toStdString())) {
            this->updateMoveHistory();
        }
    }
}

QString ChessGame::getStatusMessage(Board *b)
{
    return QString::fromStdString(b->getActivePlayerString() +
                                  " (Board status: " + b->getBoardStatusString() + ")");
}

