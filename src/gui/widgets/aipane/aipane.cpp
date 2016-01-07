#include "aipane.h"
#include "ui_aipane.h"

AiPane::AiPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AiPane)
{
    ui->setupUi(this);
}

AiPane::~AiPane()
{
    delete ui;
}
