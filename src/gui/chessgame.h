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
#include <QHBoxLayout>
#include <QListView>
#include <QListWidget>
#include <QGroupBox>
#include <QPushButton>

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

    // Draw entire board
    void drawBoard(Board * b);

public slots:
    // Slots for starting games
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

    // Move history slots
    void updateMoveHistory();
    void drawBoardSlot(QListWidgetItem * i);
    void revertMove();

private:
    // Widgets
    QWidget *container;
    // Actual playing board
    Chessboard *chessboard;
    // Move history widgets
    QGroupBox *moveHistoryBox;
    QListWidget *moveHistory;
    QPushButton *revertMoveButton;
//    // AI widgets
//    QGroupBox *aiBox;

    // Menu's
    QMenu *game_menu;

    // Game variables
    GameManager game;
    ChessLabel *activeField;
    bool boardActive;

    // Extra methods
    QString getStatusMessage(Board * b);
};

#endif // CHESSGAME_H
