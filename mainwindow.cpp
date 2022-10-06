#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <cstdio>
#include <stdio.h>
#include <iostream>
#include </opt/homebrew/Cellar/mysql/8.0.30_1/include/mysql/mysql.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <QTextStream>
#include <QDate>
#include <QDateTime>
#include <iostream>
#include <string>
#include <time.h>
#include <QDebug>
using namespace std;

struct node{
    int data;
};

struct node node1;

MYSQL *con = mysql_init(NULL);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    if (con == NULL){
            ui->label_5->setText("MySql bağlantı Hatası");
            exit(1);
        }
    if (mysql_real_connect(con, "localhost", "root", "Tahatunc2142",
              "hotel", 0, NULL, 0) == NULL)
      {
          //finish_with_error(con);
      }
    mysql_query(con, "SELECT * FROM rooms");
    MYSQL_ROW record;
    MYSQL_RES* rs = mysql_store_result(con);
    ui->pushButton_4->setEnabled(false);
    while ((record = mysql_fetch_row(rs)) != NULL) {

        if(strncmp("0", record[0], strlen("0")) == 0 && strncmp("0", record[1], strlen("0")) == 0 && strncmp("0", record[2], strlen("0")) == 0){
            ui->label_5->setText("Boş Oda Bulunamadı.");
            ui->pushButton_2->setEnabled(false);
            ui->pushButton_4->setEnabled(false);

        }
    }
    mysql_query(con, "SELECT * FROM customer_information");

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(myfunction()));
    timer->start(0);

    QDate cd = QDate::currentDate();

    ui->dateEdit->setDate(cd);
    ui->dateEdit_2->setDate(cd);

    QString currentDate = cd.toString("dd/MM/yyyy");
    std::string currentDateS = currentDate.toStdString();
    const char* currentDateP = currentDateS.c_str();

    char buffer[100];
    sprintf(buffer, "%s", currentDateP);
    //ui->pushButton_5->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    QString name;
    QString identifyNumber;
    QString age;
    QString enteryDate;
    QString leaveDate;
    QString gender;
    QString mail;
    name = ui->lineEdit->text();
    identifyNumber = ui->lineEdit_2->text();
    mail = ui->lineEdit_4->text();
    if(identifyNumber.length() != 11){
        ui->label_5->setText("Eksik TC Kimlik Bilgisi.");
    } else {
        room->identify(identifyNumber);
        int identifyCheck = 0;
        MYSQL_ROW record;
        MYSQL_RES* rs = mysql_store_result(con);
        char checkid[11];
        while ((record = mysql_fetch_row(rs)) != NULL) {
                memcpy(checkid,record[1], 11);
                if(strncmp(checkid, identifyNumber.toStdString().c_str(), 11) == 0){
                    identifyCheck = 1;
                }
            }
        mysql_free_result(rs);
        if(identifyCheck == 1){
            ui->label_5->setText("Müşteri mevcuttur.");
        } else {
            age = ui->lineEdit_3->text();
            bool gender1 = ui->radioButton->isChecked();
            bool gender2 = ui->radioButton_2->isChecked();
            if (gender1 == false && gender2 == false){
                ui->label_5->setText("Lütfen Cinsiyet Seçiniz.");
            } else {
                if (ui->radioButton->isChecked() == true){
                    //for male
                    gender = "Erkek";
                }
                if(ui->radioButton_2->isChecked() == true){
                    //for female
                    gender = "Kadın";
                }
                QDate date = ui->dateEdit->date();
                QDate date2 = ui->dateEdit_2->date();
                enteryDate = date.toString("dd/MM/yyyy");
                leaveDate = date2.toString("dd/MM/yyyy");

                char buffer[600];
                std::string nameS = name.toStdString();
                const char* nameP = nameS.c_str();

                std::string identifyNumberS = identifyNumber.toStdString();
                const char* identifyNumberP = identifyNumberS.c_str();

                std::string ageS = age.toStdString();
                const char* ageP = ageS.c_str();

                std::string genderS = gender.toStdString();
                const char* genderP = genderS.c_str();

                std::string enteryDateS = enteryDate.toStdString();
                const char* enteryDateP = enteryDateS.c_str();

                std::string leaveDateS = leaveDate.toStdString();
                const char* leaveDateP = leaveDateS.c_str();

                std::string mailS = mail.toStdString();
                const char* mailP = mailS.c_str();

                sprintf(buffer, "INSERT INTO customer_information (name, identifyNumber, age, gender, enteryDate, leaveDate, email) VALUES('%s', '%s', '%s', '%s', '%s', '%s', '%s')", nameP, identifyNumberP, ageP, genderP, enteryDateP, leaveDateP, mailP);

                if (mysql_query(con, buffer)) {

                    ui->label_5->setText("Hata");
                } else {
                    char bookingInformation[600];
                    sprintf(bookingInformation,"\"Rezervasyon bilgileriniz aşağıda belirtidiği gibidir.\n Giriş Tarihiniz: %s\n Çıkış Tarihiniz: %s\"", enteryDateP, leaveDateP);
                    char command[600];
                    sprintf(command, "/opt/homebrew/bin/sendEmail -f hoteltest21@outlook.com \\\n -t %s \\\n -s smtp-mail.outlook.com:587 \\\n -xu hoteltest21@outlook.com \\\n -xp Tahatnc2142 \\\n -o message-charset=kjklljkkj \\\n -u Rezervasyon Bilgileri \\\n -m %s", mailS.c_str(), bookingInformation);
                    system(command);
                    ui->label_5->setText("Bilgiler Başarıyla Kaydedildi.");
                }

            }
            ui->pushButton_4->setEnabled(true);
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QString identifyNumber;
    identifyNumber = ui->lineEdit_2->text();
    if(identifyNumber.length() != 11){
        ui->label_5->setText("Eksik TC Kimlik Bilgisi.");
    } else {
        mysql_query(con, "SELECT * FROM customer_information");
        MYSQL_ROW record;
        MYSQL_RES* rs = mysql_store_result(con);
        char checkid[11];
        int identifyCheck = 0;
        while ((record = mysql_fetch_row(rs)) != NULL) {
                memcpy(checkid,record[1], 11);
                if(strncmp(checkid, identifyNumber.toStdString().c_str(), 11) == 0){
                    identifyCheck = 1;
                    char buffer[600];
                    char bookingInformation[600];
                    sprintf(bookingInformation,"\"Sayın %s, Otelden çıkış işleminiz gerçekleştirilmiştir\"", record[0]);
                    char command[600];
                    sprintf(command, "/opt/homebrew/bin/sendEmail -f hoteltest21@outlook.com \\\n -t %s \\\n -s smtp-mail.outlook.com:587 \\\n -xu hoteltest21@outlook.com \\\n -xp Tahatnc2142 \\\n -o message-charset=kjklljkkj \\\n -u Otel Çıkış Bilgilendirme \\\n -m %s", record[6], bookingInformation);
                    system(command);
                    sprintf(buffer, "DELETE FROM customer_information WHERE identifyNumber = '%s'", identifyNumber.toStdString().c_str());
                    mysql_query(con, buffer);
                    ui->label_5->setText("Müşteri Silinmiştir");
                    break;
                }
            }
        mysql_free_result(rs);
        if (identifyCheck == 0){
            ui->label_5->setText("Silinmek istenen Müşteri Mevcut Değil");
        }

    }
}

/*void MainWindow::myfunction(){
    QDate cd = QDate::currentDate();
    QString cdS = cd.toString("dd/MM/yyyy");
    ui->label_11->setText(cdS);
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh:mm");
    ui->lcdNumber->display(time_text);

    int hourTime = time.hour();
    int minuteTime = time.minute();
    int secondTime = time.second();

    if(hourTime < 18){
        QPalette palette = ui->lcdNumber->palette();
        palette.setColor(palette.WindowText, Qt::black);
        palette.setColor(palette.Light, QColor(0, 0, 0));
        palette.setColor(palette.Dark, QColor(0, 0, 0));
        ui->lcdNumber->setPalette(palette);
    }

    if(hourTime == 10 && minuteTime == 0 && secondTime == 0 && node1.data == 0){

        node1.data++;
        MYSQL_ROW record;
        MYSQL_RES* rs = mysql_store_result(con);
        //int day = cd.day();
        //int month = cd.month();
        //int year = cd.year();
        string buff1;
        string buff2;

        //struct tm *tm1;
        //struct tm *tm2;
        while ((record = mysql_fetch_row(rs)) != NULL) {

            buff1 = record[4];
            buff2 = record[5];
            const char *time1 = buff1.c_str();
            struct tm tm1;
            strptime(time1, "%d/%m/%Y", &tm1);

            const char *time2 = buff2.c_str();
            struct tm tm2;
            strptime(time2, "%d/%m/%Y", &tm2);

            QDate qcd = QDate::currentDate();
            QString qscd = qcd.toString("dd/MM/yyyy");

            string strcd = qscd.toStdString();
            const char *cdtime = strcd.c_str();
            struct tm ct;
            strptime(cdtime, "%d/%m/%Y", &ct);

            char message[25];
            strftime(message, sizeof(message), "%d/%m/%Y", (const struct tm*) &ct);
            if(tm1.tm_mday - ct.tm_mday == 1 && tm1.tm_mon == ct.tm_mon && tm1.tm_year == ct.tm_year){
                char bookingInformation[600];
                sprintf(bookingInformation,"\"Sayın %s, Otele giriş gününüze 1 gün kalmıştır. Lütfen Rezervasyonunuzu unutmayınız.\"", record[0]);
                char command[600];
                char mail[100];
                memcpy(mail, record[6], strlen(record[6]));
                sprintf(command, "/opt/homebrew/bin/sendEmail -f hoteltest21@outlook.com \\\n -t %s \\\n -s smtp-mail.outlook.com:587 \\\n -xu hoteltest21@outlook.com \\\n -xp Tahatnc2142 \\\n -o message-charset=kjklljkkj \\\n -u HATIRLATMA \\\n -m %s", mail, bookingInformation);
                //QString q = QString::fromStdString(mail);
                //ui->label_5->setText(q);
                system(command);
            }
            if(tm2.tm_mday - ct.tm_mday == 1 && tm2.tm_mon == ct.tm_mon && tm2.tm_year == ct.tm_year){
                char bookingInformation[600];
                sprintf(bookingInformation,"\"Sayın %s, Otelden çıkış gününüze 1 gün kalmıştır.\"", record[0]);
                char command[600];
                char mail[100];
                memcpy(mail, record[6], strlen(record[6]));
                sprintf(command, "/opt/homebrew/bin/sendEmail -f hoteltest21@outlook.com \\\n -t %s \\\n -s smtp-mail.outlook.com:587 \\\n -xu hoteltest21@outlook.com \\\n -xp Tahatnc2142 \\\n -o message-charset=kjklljkkj \\\n -u HATIRLATMA \\\n -m %s", mail, bookingInformation);
                system(command);
            }
        }
        mysql_free_result(rs);
        mysql_close(con);
    }
    if(hourTime == 12 && minuteTime == 0 && secondTime == 0){
        node1.data = 0;
    }
}
*/

void MainWindow::myfunction(){
    QDate cd = QDate::currentDate();
    QString cdS = cd.toString("dd/MM/yyyy");
    ui->label_11->setText(cdS);
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh:mm");
    ui->lcdNumber->display(time_text);

    int hourTime = time.hour();
    int minuteTime = time.minute();
    int secondTime = time.second();

    if(hourTime < 18){
        QPalette palette = ui->lcdNumber->palette();
        palette.setColor(palette.WindowText, Qt::black);
        palette.setColor(palette.Light, QColor(0, 0, 0));
        palette.setColor(palette.Dark, QColor(0, 0, 0));
        ui->lcdNumber->setPalette(palette);
    }

    if(hourTime == 10 && minuteTime == 0 && node1.data == 0){
        node1.data++;
        mysql_query(con, "SELECT * FROM customer_information");
        MYSQL_ROW record;
        MYSQL_RES* rs = mysql_store_result(con);
        int day = cd.day();
        int month = cd.month();
        int year = cd.year();
        string buff1;
        string buff2;

        char day1[3];
        char day2[3];
        char month1[3];
        char month2[3];
        char year1[5];
        char year2[5];

        while ((record = mysql_fetch_row(rs)) != NULL) {
            memset(day1, 0, strlen(day1));
            memset(day2, 0, strlen(day2));

            memset(month1, 0, strlen(month1));
            memset(month2, 0, strlen(month2));

            memset(year1, 0, strlen(year1));
            memset(year2, 0, strlen(year2));
            //memcpy(buff1, record[4], 10);

            buff1 = record[4];
            //memcpy(buff2, record[5], 10);

            buff2 = record[5];
            buff1.copy(day1,2,0);
            buff2.copy(day2,2,0);

            buff1.copy(month1,2,3);
            buff2.copy(month2,2,3);

            buff1.copy(year1,4,6);
            buff2.copy(year2,4,6);

            int day1I = stoi(day1);
            int day2I = stoi(day2);
            int month1I = stoi(month1);
            int month2I = stoi(month2);
            int year1I = stoi(year1);
            int year2I = stoi(year2);

            if(day1I - day == 1 && month1I == month && year1I == year){
                char bookingInformation[600];
                sprintf(bookingInformation,"\"Sayın %s, Otele giriş gününze 1 gün kalmıştır. Lütfen Rezervasyonunuzu unutmayınız.\"", record[0]);
                char command[600];
                char mail[100];
                memcpy(mail, record[6], strlen(record[6]));
                sprintf(command, "/opt/homebrew/bin/sendEmail -f hoteltest21@outlook.com \\\n -t %s \\\n -s smtp-mail.outlook.com:587 \\\n -xu hoteltest21@outlook.com \\\n -xp Tahatnc2142 \\\n -o message-charset=kjklljkkj \\\n -u HATIRLATMA \\\n -m %s", mail, bookingInformation);
                QString q = QString::fromStdString(mail);
                ui->label_5->setText(q);
                system(command);
            }
            if(day2I - day == 1 && month2I == month && year2I == year){
                char bookingInformation[600];
                sprintf(bookingInformation,"\"Sayın %s, Otelden çıkış gününze 1 gün kalmıştır.\"", record[0]);
                char command[600];
                char mail[100];
                memcpy(mail, record[6], strlen(record[6]));
                sprintf(command, "/opt/homebrew/bin/sendEmail -f hoteltest21@outlook.com \\\n -t %s \\\n -s smtp-mail.outlook.com:587 \\\n -xu hoteltest21@outlook.com \\\n -xp Tahatnc2142 \\\n -o message-charset=kjklljkkj \\\n -u HATIRLATMA \\\n -m %s", mail, bookingInformation);
                system(command);
            }

        }

    }
    if(hourTime == 12 && minuteTime == 0 && secondTime == 0){
        node1.data = 0;
    }
}

void MainWindow::on_pushButton_4_clicked()
{
   room = new Rooms(this);
   room->show();
   ui->pushButton_4->setEnabled(false);
}



void MainWindow::on_pushButton_clicked()
{
    mysql_close(con);
}


void MainWindow::on_pushButton_5_clicked()
{
    employee = new Employee(this);
    employee->show();
}


void MainWindow::on_pushButton_6_clicked()
{
    addemployee = new AddEmployee(this);
    addemployee->show();
}

