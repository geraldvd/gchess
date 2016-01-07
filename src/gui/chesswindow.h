#ifndef CHESSWINDOW_H
#define CHESSWINDOW_H

// Include Qt libraries
#include <QMainWindow>
#include <QListWidgetItem>

// Include project files
#include "chesslabel.h"
#include "widgets/chessboard/chessboard.h"
#include "../gamemanager.h"
#include "../board/board.h"

namespace Ui {
    class ChessWindow;
}

class ChessWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChessWindow(QWidget *parent = 0);
    ~ChessWindow();

    // Draw entire board
    void drawBoard(Board * b);

    // Starting new game
    void newGame(const int &board_layout=0);

public slots:
    // New game dialog slot
    void newGameDialog();

    // Slot for highlighting
    void toggleHighlighting();
    void slotMovePiece();

    // Move history slots
    void updateMoveHistory();
    void drawBoardSlot(QListWidgetItem * i);
    void revertMove();

private:
    Ui::ChessWindow *ui;

    // Game variables
    GameManager game;
    ChessLabel *activeField;
    bool boardActive;

    // Extra methods
    QString getStatusMessage(Board * b);
};

#endif // CHESSWINDOW_H
