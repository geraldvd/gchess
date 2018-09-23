#ifndef AIPANE_H
#define AIPANE_H

#include <QWidget>

namespace Ui {
    class AiPane;
}

class AiPane : public QWidget
{
    Q_OBJECT

public:
    explicit AiPane(QWidget *parent = 0);
    ~AiPane();

private:
    Ui::AiPane *ui;
};

#endif // AIPANE_H
