#ifndef ADDEMPLOYEE_H
#define ADDEMPLOYEE_H

#include <QDialog>
#include "emplyeenumber.h"

namespace Ui {
class AddEmployee;
}

class AddEmployee : public QDialog
{
    Q_OBJECT

public:
    explicit AddEmployee(QWidget *parent = nullptr);
    ~AddEmployee();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AddEmployee *ui;
    EmplyeeNumber *emplyeeNumber;
};

#endif // ADDEMPLOYEE_H
