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
#include "piece/piece.h"
#include "piece/king.h"
#include "chessboard.h"
#include "board/board.h"
#include "player/player.h"
#include "chesslabel.h"


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

    // Slot for highlighting
    void toggleHighlighting();
    void slotMovePiece();

private:
    // Widgets
    Chessboard *chessboard;

    // Menu's
    QMenu *file_menu;

    // Game variables
    Board board;
    ChessLabel *activeField;
};

#endif // CHESSGAME_H
