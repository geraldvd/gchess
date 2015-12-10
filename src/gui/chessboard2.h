#ifndef CHESSBOARD2_H
#define CHESSBOARD2_H

// Include standard libraries
#include <vector>
#include <map>
#include <utility>

// Include Qt libraries
#include <QWidget>
#include <QMenu>
#include <QGridLayout>
#include <QString>

// Include project libraries
#include "chesslabel.h"

class Chessboard2 : public QWidget
{
    Q_OBJECT

public:
    // Constructors and destructor
    explicit Chessboard2(QWidget *parent = 0);
    ~Chessboard2();

    // Piece functions
    void addPiece(const Field & position, const enum PieceColor & c, const enum PieceType & p);
    void removePiece(const Field & position);
    void movePiece(const Field & from, const Field & to);
    void clearPieces();

    // Hightlight functions
    void highlightField(const Field & position);
    void unhighlightField(const Field & position);
    void clearHighlights();


private:
    // UI elements
    //Ui::Chessboard2 *ui;

    // Get image filename of piece
    QString getImageFilename(const enum PieceColor & c, const enum PieceType & p);

    // Pieces and highlighted fields
    std::map<Field,ChessLabel*> pieces;
    std::map<Field,ChessLabel*> highlights;

protected:
    void paintEvent(QPaintEvent *p2);
};

#endif // CHESSBOARD2_H
