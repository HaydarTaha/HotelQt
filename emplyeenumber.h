#ifndef EMPLYEENUMBER_H
#define EMPLYEENUMBER_H

#include <QDialog>

namespace Ui {
class EmplyeeNumber;
}

class EmplyeeNumber : public QDialog
{
    Q_OBJECT

public:
    explicit EmplyeeNumber(QWidget *parent = nullptr);
    ~EmplyeeNumber();

private:
    Ui::EmplyeeNumber *ui;
};

#endif // EMPLYEENUMBER_H
