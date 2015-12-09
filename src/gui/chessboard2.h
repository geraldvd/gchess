#ifndef CHESSBOARD2_H
#define CHESSBOARD2_H

// Include standard libraries
#include <vector>
#include <map>
#include <utility>

// Include Qt libraries
#include <QMainWindow>
#include <QMenu>
#include <QGridLayout>
#include <QString>

// Include project libraries
#include "chesslabel.h"

namespace Ui {
class Chessboard2;
}

class Chessboard2 : public QMainWindow
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

    // Hightlight functions
    void highlightField(const Field & position);
    void unhighlightField(const Field & position);
    void unhighlightAllFields();


private:
    // UI elements
    Ui::Chessboard2 *ui;
    QGridLayout *grid;
    QMenu *fileMenu;

    //
    QString getImageFilename(const enum PieceColor & c, const enum PieceType & p);

    // Pieces and highlighted fields
    std::map<Field,ChessLabel*> pieces;
    std::map<Field,ChessLabel*> highlights;
};

#endif // CHESSBOARD2_H
