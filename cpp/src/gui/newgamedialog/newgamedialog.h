#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include <QDialog>

namespace Ui {
    class NewGameDialog;
}

class NewGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewGameDialog(QWidget *parent = 0);
    ~NewGameDialog();

    int getBoardLayout() const;
    bool whiteIsComputer() const;
    bool blackIsComputer() const;

public slots:
    void setDialogState();

private:
    Ui::NewGameDialog *ui;

    // Dialog state
    int boardLayout;
    bool whiteComputer;
    bool blackComputer;
};

#endif // NEWGAMEDIALOG_H
