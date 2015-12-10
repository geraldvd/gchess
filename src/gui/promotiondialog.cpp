#include "promotiondialog.h"
#include "ui_promotiondialog.h"

#include <sstream>
#include <QPixmap>
#include <QBitmap>
#include <QIcon>
#include <QDebug>

using namespace std;

PromotionDialog::PromotionDialog(const enum PieceColor &c, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PromotionDialog),
    promotionType(PROMOTION_QUEEN)
{
    this->ui->setupUi(this);

    // Window size policy
    this->setFixedSize(this->sizeHint());

    // Button icons
    string iconColor = c==WHITE ? "white" : "black";

    // Queen
    {
        stringstream ss;
        ss << "../images/queen_" << iconColor << ".png";
        QPixmap pm(QString::fromStdString(ss.str()));
        QIcon buttonIcon(pm);
        this->ui->buttonQueen->setIcon(buttonIcon);
        this->ui->buttonQueen->setIconSize(pm.rect().size());
        this->ui->buttonQueen->setText("");
        this->ui->buttonQueen->setDefault(true);
    }

    // Rook
    {
        stringstream ss;
        ss << "../images/rook_" << iconColor << ".png";
        QPixmap pm(QString::fromStdString(ss.str()));
        QIcon buttonIcon(pm);
        this->ui->buttonRook->setIcon(buttonIcon);
        this->ui->buttonRook->setIconSize(pm.rect().size());
        this->ui->buttonRook->setText("");
    }

    // Knight
    {
        stringstream ss;
        ss << "../images/knight_" << iconColor << ".png";
        QPixmap pm(QString::fromStdString(ss.str()));
        QIcon buttonIcon(pm);
        this->ui->buttonKnight->setIcon(buttonIcon);
        this->ui->buttonKnight->setIconSize(pm.rect().size());
        this->ui->buttonKnight->setText("");
    }

    // Bishop
    {
        stringstream ss;
        ss << "../images/bishop_" << iconColor << ".png";
        QPixmap pm(QString::fromStdString(ss.str()));
        QIcon buttonIcon(pm);
        this->ui->buttonBishop->setIcon(buttonIcon);
        this->ui->buttonBishop->setIconSize(pm.rect().size());
        this->ui->buttonBishop->setText("");
    }

    // Signals and slots
    connect(this->ui->buttonQueen, SIGNAL(clicked()), this, SLOT(slotQueen()));

}

PromotionDialog::~PromotionDialog()
{
    delete this->ui;
}

MoveType PromotionDialog::getPromotionType() const
{
    return this->promotionType;
}

void PromotionDialog::slotQueen()
{
    this->promotionType = PROMOTION_QUEEN;
    this->accept();
}

void PromotionDialog::slotRook()
{
    this->promotionType = PROMOTION_ROOK;
    this->accept();
}

void PromotionDialog::slotKnight()
{
    this->promotionType = PROMOTION_KNIGHT;
    this->accept();
}

void PromotionDialog::slotBishop()
{
    this->promotionType = PROMOTION_BISHOP;
    this->accept();
}
