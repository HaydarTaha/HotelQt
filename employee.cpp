#include "employee.h"
#include "ui_employee.h"
#include </opt/homebrew/Cellar/mysql/8.0.30_1/include/mysql/mysql.h>
#include <QDate>
#include <QDateTime>
#include <string>
#include <string.h>

MYSQL *conect2 = mysql_init(NULL);

Employee::Employee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Employee)
{
    ui->setupUi(this);
    if (conect2 == NULL){
            ui->label->setText("MySql bağlantı Hatası");
        }
    if (mysql_real_connect(conect2, "localhost", "root", "Tahatunc2142","hotel", 0, NULL, 0) == NULL){

    }
    char buffName[200];
    char buffDay[100];
    char buffType[100];
    char dayArr[15];
    memset(dayArr, 0, 15);
    QDate cd = QDate::currentDate();
    QString day = cd.toString("dddd");
    std::string dayS = day.toStdString();
    const char* dayP = dayS.c_str();
    memcpy(dayArr,dayP,strlen(dayP));
    mysql_query(conect2, "SELECT * FROM employee_t");
    MYSQL_ROW record;
    MYSQL_RES* rs = mysql_store_result(conect2);
    while ((record = mysql_fetch_row(rs)) != NULL) {
        memset(buffName, 0, 200);
        memset(buffDay, 0, 100);
        memset(buffType, 0, 100);
        memcpy(buffName,record[0],strlen(record[0]));
        memcpy(buffType,record[1],strlen(record[1]));
        memcpy(buffDay,record[2],strlen(record[2]));
        if(strncmp(buffDay, dayArr, strlen(dayArr)) == 0){
            if (strncmp(buffType, "1", strlen("1")) == 0){
                ui->label_2->setText(QString::fromStdString(buffName));
            }
            if (strncmp(buffType, "2", strlen("2")) == 0){
                ui->label_4->setText(QString::fromStdString(buffName));
            }
            if (strncmp(buffType, "3", strlen("3")) == 0){
                ui->label_6->setText(QString::fromStdString(buffName));
            }
            if (strncmp(buffType, "4", strlen("4")) == 0){
                ui->label_8->setText(QString::fromStdString(buffName));
            }
            if (strncmp(buffType, "5", strlen("5")) == 0){
                ui->label_10->setText(QString::fromStdString(buffName));
            }
            if (strncmp(buffType, "6", strlen("6")) == 0){
                ui->label_12->setText(QString::fromStdString(buffName));
            }
            if (strncmp(buffType, "7", strlen("7")) == 0){
                ui->label_14->setText(QString::fromStdString(buffName));
            }
            if (strncmp(buffType, "8", strlen("8")) == 0){
                ui->label_16->setText(QString::fromStdString(buffName));
            }
            memset(buffName, 0, 200);
            memset(buffDay, 0, 100);
            memset(buffType, 0, 100);
        }
    }
    mysql_close(conect2);
}



Employee::~Employee()
{
    delete ui;
}
