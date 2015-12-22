#ifndef CHESSBOARD_H
#define CHESSBOARD_H

// Include standard libraries
#include <vector>
#include <map>
#include <utility>
#include <string>

// Include Qt libraries
#include <QWidget>
#include <QMenu>
#include <QGridLayout>
#include <QString>
#include <QLabel>

// Include project libraries
#include "utils.h"
#include "chesslabel.h"

class Chessboard : public QLabel
{
    Q_OBJECT

public:
    // Constructors and destructor
    explicit Chessboard(QWidget *parent = 0);
    ~Chessboard();

    // Piece functions
    void addPiece(const unsigned int & position, const PieceColor & c, const PieceType & p);
    void removePiece(const unsigned int & position);
    void movePiece(const unsigned int & from, const unsigned int & to);
    void clearPieces();

    // Hightlight functions
    void highlightField(const Move &move);
    void unhighlightField(const unsigned int & position);
    void clearHighlights();
    void checkField(const unsigned int & position);
    void unCheckField();


private:
    // Parent needed for signals and slots (moving pieces)
    QWidget *parent;

    // Get image filename of piece
    QString getImageFilename(const PieceColor & c, const PieceType & p);
    QString getPieceHTML(const PieceColor & c, const PieceType & p);

    // Pieces and highlighted fields
    std::map<unsigned int,ChessLabel*> pieces;
    std::map<unsigned int,ChessLabel*> highlights;
    ChessLabel* check_field;

public:
//    void paintEvent(QPaintEvent *p2);
};

#endif // CHESSBOARD_H
