#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "rooms.h"
#include "employee.h"
#include "addemployee.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

public slots:
    void myfunction();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    Rooms *room;
    Employee *employee;
    AddEmployee *addemployee;

};
#endif // MAINWINDOW_H
