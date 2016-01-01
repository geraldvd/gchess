#ifndef CHESSGAME_H
#define CHESSGAME_H

// Include standard libraries
#include <map>

// Include Qt libraries
#include <QMainWindow>
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>
#include <QVBoxLayout>

// Include project files
#include "chessboard.h"
#include "chesslabel.h"
#include "../gamemanager.h"


class ChessGame : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor and destructor
    explicit ChessGame(QWidget *parent=0);
    ~ChessGame();

signals:

public slots:
    // Slot for starting new game
    void newGame(const int &board_layout=0);
    void promotionTest();
    void castlingTest();
    void moveIntoCheckTest();
    void moveOutOfCheckTest();
    void staleMateTest();
    void enPassantTest();

    // Slot for highlighting
    void toggleHighlighting();
    void slotMovePiece();

private:
    // Widgets
    Chessboard *chessboard;

    // Menu's
    QMenu *game_menu;

    // Game variables
    GameManager game;
    ChessLabel *activeField;

    // Extra methods
    QString getStatusMessage();
};

#endif // CHESSGAME_H
