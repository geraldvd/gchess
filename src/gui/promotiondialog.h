#ifndef PROMOTIONDIALOG_H
#define PROMOTIONDIALOG_H

#include <QDialog>
#include <game.h>

namespace Ui {
class PromotionDialog;
}

class PromotionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PromotionDialog(const PieceColor & c, QWidget *parent = 0);
    ~PromotionDialog();

    PromotionType getPromotionType() const;
    PieceColor getPieceColor() const;
    PieceType getPieceType() const;

private:
    Ui::PromotionDialog *ui;

    // Promotion type
    PromotionType promotionType;

    // Extra information
    PieceColor pieceColor;
    PieceType pieceType;


public slots:
    void slotQueen();
    void slotRook();
    void slotBishop();
    void slotKnight();


};

#endif // PROMOTIONDIALOG_H
