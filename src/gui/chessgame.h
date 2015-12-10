#ifndef CHESSGAME_H
#define CHESSGAME_H

// Include Qt files
#include <QMainWindow>
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>

// Include project files
#include "chessboard2.h"
#include "game.h"


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
    void newGame();

private:
    // Widgets
    QMenuBar *menubar;
    Chessboard2 *chessboard;
    QStatusBar *statusbar;

    // Menu's
    QMenu *file_menu;

    // Game variables
    Game game;
};

#endif // CHESSGAME_H
