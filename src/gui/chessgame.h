#ifndef CHESSGAME_H
#define CHESSGAME_H

// Include standard libraries
#include <map>

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

    // Piece functions (calling chessboard methods)
    void addPiece(Piece *p);

    // Highlight functions
    void highlightMoves(Piece *p);

signals:

public slots:
    // Slot for starting new game
    void newGame();

    // Slot for highlighting
    void toggleHighlighting();
    void slotMovePiece();

private:
    // Widgets
    QMenuBar *menubar;
    Chessboard2 *chessboard;
    QStatusBar *statusbar;

    // Menu's
    QMenu *file_menu;

    // Game variables
    Game game;
    std::map<Field,Piece*> pieces;
    ChessLabel *activeField;
};

#endif // CHESSGAME_H
