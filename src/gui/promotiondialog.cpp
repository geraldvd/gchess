// Include standard libraries
#include <sstream>

// Include Qt libraries
#include <QPixmap>
#include <QBitmap>
#include <QIcon>
#include <QDebug>

// Include project files
#include "promotiondialog.h"
#include "ui_promotiondialog.h"

// Specify namespaces
using namespace std;

PromotionDialog::PromotionDialog(const enum PieceColor &c, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PromotionDialog),
    promotionType(PT_QUEEN),
    pieceColor(c),
    pieceType(QUEEN)
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
    connect(this->ui->buttonRook, SIGNAL(clicked()), this, SLOT(slotRook()));
    connect(this->ui->buttonBishop, SIGNAL(clicked()), this, SLOT(slotBishop()));
    connect(this->ui->buttonKnight, SIGNAL(clicked()), this, SLOT(slotKnight()));

}

PromotionDialog::~PromotionDialog()
{
    delete this->ui;
}

PromotionType PromotionDialog::getPromotionType() const
{
    return this->promotionType;
}

PieceColor PromotionDialog::getPieceColor() const
{
    return this->pieceColor;
}

PieceType PromotionDialog::getPieceType() const
{
    return this->pieceType;
}

void PromotionDialog::slotQueen()
{
    this->promotionType = PT_QUEEN;
    this->pieceType = QUEEN;
    this->accept();
}

void PromotionDialog::slotRook()
{
    this->promotionType = PT_ROOK;
    this->pieceType = ROOK;
    this->accept();
}

void PromotionDialog::slotKnight()
{
    this->promotionType = PT_KNIGHT;
    this->pieceType = KNIGHT;
    this->accept();
}

void PromotionDialog::slotBishop()
{
    this->promotionType = PT_BISHOP;
    this->pieceType = BISHOP;
    this->accept();
}
