#ifndef CHESSBOARD_H
#define CHESSBOARD_H

// Qt include files
#include <QMainWindow>
#include <QGridLayout>
#include <QMenu>
#include <QLabel>
#include <QList>
#include <QPair>
#include <QString>

// Standard library include files
#include <utility>
#include <map>

// Project include files
#include "game.h"
#include "piecelabel.h"

namespace Ui {
class Chessboard;
}

class Chessboard : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor and destructor
    explicit Chessboard(QWidget *parent = 0);
    ~Chessboard();

    // Initializers
    void initBoard();

    // Highlight methods
    void drawCircleOnField(const Field & position);
    void removeCircleFromField(const Field & position);
    void highlightPossibleMoves(Piece *p);

    // Piece methods
    void addPiece(Piece *p);
    void removePiece(const Field & position);
    void movePiece(const Field & from, const Field & to);

    // Setters and getters
    void setStatusBar(const QString & text);

    // Pixel size of square board
    const static int pixelSizeBoard;

    void test();

public slots:
    // Slot for highlighting and unhighlighting moves
    void toggleHighlightMoves();

    // Slot for moving to certain field (specified by signal sender() )
    void movePieceSlot();

    // Slot for starting new game
    void newGame();

signals:
    void doUpdate();

private:
    // UI elements
    Ui::Chessboard *ui;
    QGridLayout * grid;
    std::vector<PieceLabel*> squares;
    QMenu * fileMenu;

    // Pieces currently on board
    std::map<Field,PieceLabel*> pieces;


    // Game variables
    Game game;

    // Highlight variables
    Piece* pieceWithHighlightedMoves;
    std::vector<Field> possibleMoves;
};

#endif // CHESSBOARD_H
