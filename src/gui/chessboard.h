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
    void clearPieces();

    // Highlight methods
    void drawCircleOnField(const Field & position);
    void removeCircleFromField(const Field & position);
    void highlightPossibleMoves(Piece *p);
    void unhighlightPossibleMoves();

    // Piece methods
    void addPiece(Piece *p);
    void addPiece(const Field &position, const std::string &type, const PieceColor &c);
    void removePiece(const Field & position);
    void movePiece(const Field & from, const Field & to);
    void movePiece(Piece *p, const Field & from);

    // Pixel size of square board
    const static int pixelSizeBoard;

public slots:
    // Slot for highlighting and unhighlighting moves
    void toggleHighlightMoves();

    // Slot for moving to certain field (specified by signal sender() )
    void movePieceSlot();

    // Slot for starting new game
    void newGame();

private:
    // UI elements
    Ui::Chessboard *ui;
    QGridLayout * grid;
    QMenu * fileMenu;

    // Squares and pieces
    std::map<Field,PieceLabel*> squares;
    std::map<Field,PieceLabel*> pieces;

    // Game variables
    Game game;

    // Highlight variables
    Piece* pieceWithHighlightedMoves;
    std::vector<Field> possibleMoves;
};

#endif // CHESSBOARD_H
