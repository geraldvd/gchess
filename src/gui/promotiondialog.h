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
    explicit PromotionDialog(const enum PieceColor & c, QWidget *parent = 0);
    ~PromotionDialog();

    enum PromotionType getPromotionType() const;
    enum PieceColor getPieceColor() const;
    enum PieceType getPieceType() const;

private:
    Ui::PromotionDialog *ui;

    // Promotion type
    enum PromotionType promotionType;

    // Extra information
    enum PieceColor pieceColor;
    enum PieceType pieceType;


public slots:
    void slotQueen();
    void slotRook();
    void slotBishop();
    void slotKnight();


};

#endif // PROMOTIONDIALOG_H
