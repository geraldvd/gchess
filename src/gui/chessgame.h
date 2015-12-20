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
#include "chessboard.h"
#include "../game/game.h"
#include "chesslabel.h"


class ChessGame : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor and destructor
    explicit ChessGame(QWidget *parent=0);
    ~ChessGame();

    // Piece functions (calling chessboard methods)
//    void addPiece(Piece *p);

signals:

public slots:
    // Slot for starting new game
    void newGame();

    // Slot for highlighting
    void toggleHighlighting();
    void slotMovePiece();

private:
    // Widgets
    Chessboard *chessboard;

    // Menu's
    QMenu *file_menu;

    // Game variables
    Game game;
    ChessLabel *activeField;
};

#endif // CHESSGAME_H
