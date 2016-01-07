// Include Qt libraries
#include <QDebug>

// Include project files
#include "chesswindow.h"
#include "ui_chesswindow.h"
#include "promotiondialog/promotiondialog.h"
#include "newgamedialog/newgamedialog.h"
#include "../piece/king.h"

ChessWindow::ChessWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChessWindow),

    activeField(NULL),
    boardActive(false)
{
    ui->setupUi(this);

    // Start game
    this->newGame();

    // Setup engine
    this->updateEngine();


    // Setup signals and slots
    connect(this->ui->revertButton, SIGNAL(clicked(bool)), this, SLOT(revertMove()));
    connect(this->ui->menuGame->actions().at(0), SIGNAL(triggered(bool)), this, SLOT(newGameDialog()));
}

ChessWindow::~ChessWindow()
{
    delete ui;
}

void ChessWindow::drawBoard(Board * b)
{
    // Empty board
    this->ui->chessBoard->clearPieces();
    this->ui->chessBoard->unCheckField();
    this->ui->chessBoard->clearHighlights();

    // Draw pieces
    for(auto &p : b->getPieces()) {
        this->ui->chessBoard->addPiece(p->getTile()->getPosition(), p->getColor(), p->getType());
    }

    // Draw board status
    this->statusBar()->showMessage(this->getStatusMessage(b));

    // Highlight if king is in check position
    if(b->activeKingCheck()) {
        this->ui->chessBoard->checkField(b->getActiveKing()->getTile()->getPosition());
    }
}

void ChessWindow::newGame(const int & board_layout)
{
    // Start new game
    this->game.initBoard(board_layout);

    // Draw board
    this->drawBoard(this->game.getBoard());
    this->boardActive = true;
    this->updateMoveHistory();
}

void ChessWindow::updateEngine()
{
    this->engine = MoveTree(3, this->game.getBoard()->get());
    this->ui->numPlies->setText(QString::number(this->engine.getNumPlies()));
    this->ui->numMoves->setText(QString::number(this->engine.getNumMoves()));
    this->ui->duration->setText(QString::number(this->engine.getDurationSeconds()));
}

void ChessWindow::newGameDialog()
{
    NewGameDialog ngd;
    if(ngd.exec()) {
        this->newGame(ngd.getBoardLayout());
        qDebug() << "Board layout: " << ngd.getBoardLayout() << endl
                 << "White computer? " << ngd.whiteIsComputer() << ", Black computer? " << ngd.blackIsComputer() << endl;
    }
}

void ChessWindow::toggleHighlighting()
{
    // Only do this if board is active (i.e., current)
    if(this->boardActive) {
        // Obtain piece to be toggled
        ChessLabel* l = dynamic_cast<ChessLabel*>(sender());

        // Check whether already highlighted and toggle
        if(l == this->activeField) {
            this->ui->chessBoard->clearHighlights();
            this->activeField = NULL;
        } else {
            // Check whether piece is allowed to move
            if(this->game.getBoard()->getActivePlayer() == this->game.getBoard()->getTile(l->getPosition())->getPiece()->getColor()) {
                this->activeField = l;

                // Clear old highlights
                this->ui->chessBoard->clearHighlights();

                // Highlight moves
                for(auto &m : this->game.getBoard()->getMoves()) {
                    // Only highlight moves of clicked piece
                    if(*m.getMovingPiece()->getTile() == l->getPosition()) {
                        this->ui->chessBoard->highlightField(m);
                    }
                }
            } else {
                this->ui->chessBoard->clearHighlights();
                this->activeField = NULL;
            }
        }
    }
}

void ChessWindow::slotMovePiece()
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
                            this->ui->chessBoard->removePiece(from.getPosition());
                            this->ui->chessBoard->addPiece(to->getPosition().getPosition(), pd.getPieceColor(), pd.getPieceType());
                        }
                    } else {
                        // Assume queen
                        to->getMove()->setPromotionType(PT_QUEEN);
                        if(this->game.move(from, to->getMove()->getDestination(), PT_QUEEN) == MS_OK) {
                            this->ui->chessBoard->removePiece(from.getPosition());
                            this->ui->chessBoard->addPiece(to->getPosition().getPosition(), pd.getPieceColor(), QUEEN);
                        }
                    }
                }
                break;
            case MT_CASTLING:
                if(this->game.move(from, to->getMove()->getDestination()) == MS_OK) {
                    // Move king
                    this->ui->chessBoard->movePiece(from.getPosition(), to->getPosition().getPosition());
                    // Move rook
                    if(this->game.getBoard()->getTile(to->getPosition())->getX() == 2) {
                        this->ui->chessBoard->movePiece(to->getPosition().getPosition()-2, to->getPosition().getPosition()+1);
                    } else {
                        this->ui->chessBoard->movePiece(to->getPosition().getPosition()+1, to->getPosition().getPosition()-1);
                    }
                }
                break;
            case MT_ENPASSANT:
                if(this->game.move(from, to->getMove()->getDestination()) == MS_OK) {
                    if(this->game.getBoard()->getTile(to->getPosition())->getPiece()->getColor() == WHITE) {
                        this->ui->chessBoard->removePiece(to->getPosition().getPosition()-8);
                    } else {
                        this->ui->chessBoard->removePiece(to->getPosition().getPosition()+8);
                    }
                    this->ui->chessBoard->movePiece(from.getPosition(), to->getPosition().getPosition());
                }
                break;
            case MT_PAWNJUMP:
            case MT_NORMAL:
                if(this->game.move(from, to->getMove()->getDestination()) == MS_OK) {
                    this->ui->chessBoard->movePiece(from.getPosition(), to->getPosition().getPosition());
                }
                break;
            case MT_NONE:
                // Do nothing
                return;
            }

            // Unhighlight all fields
            this->activeField = NULL;
            this->ui->chessBoard->clearHighlights();

            // Unhighlight check position
            this->ui->chessBoard->unCheckField();

            // Set new active player
            this->statusBar()->showMessage(this->getStatusMessage(this->game.getBoard()));


            // Highlight if king is in check position; Note: only one king can be check - TODO: is this a task for the gui?
            if(this->game.getBoard()->activeKingCheck()) {
                this->ui->chessBoard->checkField(this->game.getBoard()->getActiveKing()->getTile()->getPosition());
            }

            // Update move history pane
            this->updateMoveHistory();

            // Update engine
            this->updateEngine();
        }
    }
}

void ChessWindow::updateMoveHistory() {
    this->ui->moveHistoryList->clear();

    for(auto &mh : this->game.getMoveHistory()) {
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(mh.first.getMoveString()));
        item->setToolTip(QString::fromStdString(mh.second));
        this->ui->moveHistoryList->addItem(item);
    }

    // Add current board
    QListWidgetItem *item = new QListWidgetItem("- current -");
    item->setToolTip(QString::fromStdString(this->game.getBoard()->get()));
    this->ui->moveHistoryList->addItem(item);

    connect(this->ui->moveHistoryList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(drawBoardSlot(QListWidgetItem*)));
    emit this->ui->moveHistoryList->itemClicked(item);
}

void ChessWindow::drawBoardSlot(QListWidgetItem *i)
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

void ChessWindow::revertMove()
{
    if(this->ui->moveHistoryList->selectedItems().size() > 0 && this->ui->moveHistoryList->selectedItems().at(0)->text() != "- current -") {
        // Revert move
        if(this->game.revertMove(this->ui->moveHistoryList->selectedItems().at(0)->toolTip().toStdString())) {
            this->updateMoveHistory();
        }
    }
}

QString ChessWindow::getStatusMessage(Board *b)
{
    return QString::fromStdString(b->getActivePlayerString() +
                                  " (Board status: " + b->getBoardStatusString() + ")");
}
