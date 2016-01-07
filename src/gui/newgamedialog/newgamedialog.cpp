#include "newgamedialog.h"
#include "ui_newgamedialog.h"

NewGameDialog::NewGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGameDialog),

    boardLayout(0),
    whiteComputer(false),
    blackComputer(true)
{
    ui->setupUi(this);

    // Signals and slots
    connect(this->ui->buttonBox, SIGNAL(accepted()), this, SLOT(setDialogState()));
}

NewGameDialog::~NewGameDialog()
{
    delete ui;
}

int NewGameDialog::getBoardLayout() const
{
    return this->boardLayout;
}

bool NewGameDialog::whiteIsComputer() const
{
    return this->whiteComputer;
}

bool NewGameDialog::blackIsComputer() const
{
    return this->blackComputer;
}

void NewGameDialog::setDialogState()
{
    this->boardLayout = this->ui->boardLayout->currentIndex();
    this->whiteComputer = this->ui->whiteComputerRadio->isChecked();
    this->blackComputer = this->ui->blackComputerRadio->isChecked();
}
