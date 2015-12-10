#include "chessgame.h"

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

void ChessGame::addPiece(Piece *p)
{
    this->pieces[p->getPosition()] = p;
    this->chessboard->addPiece(p->getPosition(), p->getColor(), p->getType());
}

void ChessGame::highlightMoves(Piece *p)
{
    this->chessboard->clearHighlights();
    for(auto &m : p->getMoves()) {
        this->chessboard->highlightField(m.first);
    }
}

void ChessGame::newGame()
{
    // Empty board
    this->chessboard->clearPieces();
    this->chessboard->clearHighlights();

    // Start new game
    this->game.initTest();
    this->statusBar()->showMessage(QString::fromStdString(this->game.getActivePlayerString()));

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

        // TODO: Normal discards possible promotions!
        if(this->game.move(this->pieces[this->activeField->getField()], Move(to->getField(), NORMAL))) {
            // Check castling
            if(this->pieces[from]->getMoveType() == CASTLING) {
                Piece* r;
                int xStep;
                if(this->pieces.find(Field(to->getField().first+1, to->getField().second)) != this->pieces.end()) {
                    r = this->pieces[Field(to->getField().first+1, to->getField().second)];
                    xStep = -2;
                } else if(this->pieces.find(Field(to->getField().first-1, to->getField().second)) != this->pieces.end()) {
                    r = this->pieces[Field(to->getField().first-1, to->getField().second)];
                    xStep = 2;
                } else {
                    // This should never happen!
                    qDebug() << "This message should never be seen!!" << endl;
                }

                Field from = Field(r->getPosition().first-xStep, r->getPosition().second);
                this->chessboard->movePiece(from, r->getPosition());

                // Update piece position (in this class)
                this->pieces[r->getPosition()] = this->pieces[from];
                this->pieces.erase(from);
            }

            // Check promotion - TODO should be handled by game class!
            if(this->pieces[from]->getMoveType() == PROMOTION_QUEEN || this->pieces[from]->getMoveType() == PROMOTION_ROOK ||
                    this->pieces[from]->getMoveType() == PROMOTION_KNIGHT || this->pieces[from]->getMoveType() == PROMOTION_BISHOP) {
                PromotionDialog pd(this->pieces[from]->getColor());
                if(pd.exec()) {
                    Piece* p = this->pieces[from];
                    Piece* p2;
                    switch(pd.getPromotionType()) {
                    case PROMOTION_ROOK:
                        p2 = new Rook(p->getPosition().first, p->getPosition().second, p->getColor(), true);
                        break;
                    case PROMOTION_KNIGHT:
                        p2 = new Knight(p->getPosition().first, p->getPosition().second, p->getColor(), true);
                        break;
                    case PROMOTION_BISHOP:
                        p2 = new Bishop(p->getPosition().first, p->getPosition().second, p->getColor(), true);
                        break;
                    default:
                        p2 = new Queen(p->getPosition().first, p->getPosition().second, p->getColor(), true);
                        break;
                    }
                    this->pieces[from] = p2;
                    delete p;
                }
            }

            // Move piece on board
            this->chessboard->movePiece(this->activeField->getField(), to->getField());

            // Update piece positions (in this class)
            this->pieces[to->getField()] = this->pieces[from];
            this->pieces.erase(from);

            // Unhighlight all fields
            this->activeField = NULL;
            this->chessboard->clearHighlights();

            // Unhighlight check position
            this->chessboard->unCheckField();

            // Highlight if king is in check position
            if(this->game.getPlayerCheck()) {
                if(this->game.getPlayerCheck() == WHITE) {
                    // White king in check position
                    for(auto &p : this->pieces) {
                        if(p.second->getType() == KING && p.second->getColor() == WHITE) {
                            this->chessboard->checkField(p.second->getPosition());
                        }
                    }
                } else {
                    // Black king in check position
                    for(auto &p : this->pieces) {
                        if(p.second->getType() == KING && p.second->getColor() == BLACK) {
                            this->chessboard->checkField(p.second->getPosition());
                        }
                    }
                }
            }

            // Set new active player
            this->statusBar()->showMessage(QString::fromStdString(this->game.getActivePlayerString()));
        }
    }
}

