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
#include "chesslabel.h"

class Chessboard : public QLabel
{
    Q_OBJECT

public:
    // Constructors and destructor
    explicit Chessboard(QWidget *parent = 0);
    ~Chessboard();

    // Piece functions
    void addPiece(const Field & position, const enum PieceColor & c, const enum PieceType & p);
    void removePiece(const Field & position);
    void movePiece(const Field & from, const Field & to);
    void clearPieces();

    // Hightlight functions
    void highlightField(const Field & position);
    void unhighlightField(const Field & position);
    void clearHighlights();
    void checkField(const Field & position);
    void unCheckField();


private:
    // Parent needed for signals and slots (moving pieces)
    QWidget *parent;

    // Get image filename of piece
    QString getImageFilename(const enum PieceColor & c, const enum PieceType & p);
    QString getPieceHTML(const enum PieceColor & c, const enum PieceType & p);

    // Pieces and highlighted fields
    std::map<Field,ChessLabel*> pieces;
    std::map<Field,ChessLabel*> highlights;
    ChessLabel* check_field;

public:
//    void paintEvent(QPaintEvent *p2);
};

#endif // CHESSBOARD_H
