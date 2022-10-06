#include "emplyeenumber.h"
#include "ui_emplyeenumber.h"

EmplyeeNumber::EmplyeeNumber(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmplyeeNumber)
{
    ui->setupUi(this);
}

EmplyeeNumber::~EmplyeeNumber()
{
    delete ui;
}
