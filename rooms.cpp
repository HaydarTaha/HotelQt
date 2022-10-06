#include "rooms.h"
#include "ui_rooms.h"
#include </opt/homebrew/Cellar/mysql/8.0.30_1/include/mysql/mysql.h>
#include <QDebug>
using namespace std;

struct id{
    QString identify;
};
struct id idStruct;

struct checkSql{
    int roomNum;
};

struct checkSql room0S;
struct checkSql room1S;
struct checkSql room2S;

MYSQL *conect = mysql_init(NULL);


Rooms::Rooms(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Rooms)
{
    if (conect == NULL){
            ui->label->setText("MySql bağlantı Hatası");
        }
    if (mysql_real_connect(conect, "localhost", "root", "Tahatunc2142",
              "hotel", 0, NULL, 0) == NULL)
      {
          ui->label->setText("Bağlantıda Sorun asd");
      }

    mysql_query(conect, "SELECT * FROM rooms");
    MYSQL_ROW record;
    MYSQL_RES* rs = mysql_store_result(conect);
    //QString std;
    while ((record = mysql_fetch_row(rs)) != 0) {
        string room0Str = record[0];
        string room1Str = record[1];
        string room2Str = record[2];

        room0S.roomNum = stoi(room0Str);
        room1S.roomNum = stoi(room1Str);
        room2S.roomNum = stoi(room2Str);
    }


    ui->setupUi(this);
    int roomDefault = 10;
    int temp;
    ui->label_5->setText(QString::fromStdString(""));
    ui->label_6->setText(QString::fromStdString(""));
    ui->label_7->setText(QString::fromStdString(""));

    if(room0S.roomNum == 0){
        ui->label_5->setText(QString::fromStdString(":Mevcut Değil"));
    } else {
        int price = 100;
        temp = roomDefault - room0S.roomNum;
        price = price + temp*price;
        char room0C[35];
        sprintf(room0C,"Oda Sayısı:%d Fiyat: %d", room0S.roomNum, price);
        ui->label_5->setText(QString::fromStdString(room0C));
    }
    if(room1S.roomNum == 0){
        ui->label_6->setText(QString::fromStdString(":Mevcut Değil"));
    } else {
        int price = 200;
        temp = roomDefault - room1S.roomNum;
        price = price + temp*price;
        char room1C[35];
        sprintf(room1C,"Oda Sayısı:%d Fiyat: %d", room1S.roomNum, price);
        ui->label_6->setText(QString::fromStdString(room1C));
    }
    if(room2S.roomNum == 0){
        ui->label_7->setText(QString::fromStdString(":Mevcut Değil"));
    } else {
        int price = 200;
        temp = roomDefault - room2S.roomNum;
        price = price + temp*price;
        char room2C[35];
        sprintf(room2C,"Oda Sayısı:%d Fiyat: %d", room2S.roomNum, price);
        ui->label_7->setText(QString::fromStdString(room2C));
    }

    if(room0S.roomNum == 0 && room1S.roomNum == 0 && room2S.roomNum == 0){
        ui->pushButton_2->setEnabled(false);
    }

    QPixmap pix1("/Users/taha/QtProjects/untitled/city-standart-oda-2_810x520.jpg");
    QPixmap pix2("/Users/taha/QtProjects/untitled/bogaz-otelleri-istanbul.jpg");
    QPixmap pix3("/Users/taha/QtProjects/untitled/Murat-Reis-Ayvalik-Oda-23018.jpg");

    ui->image1->setPixmap(pix1.scaled(1920/8, 1105/8));
    ui->image2->setPixmap(pix2.scaled(1920/8, 1105/8));
    ui->image3->setPixmap(pix3.scaled(1920/8, 1105/8));
}

Rooms::~Rooms()
{
    delete ui;
}

void Rooms::identify(QString dataId){
    idStruct.identify = dataId;
}


void Rooms::on_pushButton_2_clicked()
{

    if (ui->radioButton->isChecked() == true){
        if (room0S.roomNum == 0){
            ui->label_5->setText(QString::fromStdString(":Mevcut Değil"));
        } else{
            room0S.roomNum = room0S.roomNum - 1;
            char buffRoom[200];
            sprintf(buffRoom, "UPDATE rooms SET roomType0 = %d", room0S.roomNum);
            if (mysql_query(conect, buffRoom)) {
             ui->label->setText("Hata room0S");
           }
            memset(buffRoom, 0, 200);
            char room0C[25];
            sprintf(room0C,"Oda Sayısı:%d", room0S.roomNum);
            ui->label_5->setText(QString::fromStdString(room0C));
        }
    }
    if (ui->radioButton_2->isChecked() == true){
        if (room1S.roomNum == 0){
            ui->label_6->setText(QString::fromStdString(":Mevcut Değil"));
        } else{
            room1S.roomNum = room1S.roomNum - 1;
            char buffRoom[200];
            sprintf(buffRoom, "UPDATE rooms SET roomType1 = %d", room1S.roomNum);
            if (mysql_query(conect, buffRoom)) {
             ui->label->setText("Hata room1S");
           }
            memset(buffRoom, 0, 200);
            char room1C[25];
            sprintf(room1C,"Oda Sayısı:%d", room1S.roomNum);
            ui->label_6->setText(QString::fromStdString(room1C));
        }
    }
    if (ui->radioButton_3->isChecked() == true){
        if (room2S.roomNum == 0){
            ui->label_7->setText(QString::fromStdString(":Mevcut Değil"));
        } else {
            room2S.roomNum = room2S.roomNum - 1;
            char buffRoom[200];
            sprintf(buffRoom, "UPDATE rooms SET roomType2 = '%d'", room2S.roomNum);
            if (mysql_query(conect, buffRoom)) {
             ui->label->setText("Hata room2S");
           }
            memset(buffRoom, 0, 200);
            char room2C[25];
            sprintf(room2C,"Oda Sayısı:%d", room2S.roomNum);
            ui->label_7->setText(QString::fromStdString(room2C));
        }
    }

    //Üst kısım çalışıyor elleme bir daha
    QString dataId = idStruct.identify;
    std::string dataIdS = dataId.toStdString();
    const char* dataIdC = dataIdS.c_str();

    if (ui->radioButton->isChecked() == true && ui->radioButton_2->isChecked() == false && ui->radioButton_3->isChecked() == false){
        char buff[200];
        sprintf(buff, "UPDATE customer_information SET room = '0' WHERE identifyNumber = '%s'", dataIdC);
       if (mysql_query(conect, buff)) {
         //ui->label->setText("Hata");
       }

    }
    if (ui->radioButton->isChecked() == false && ui->radioButton_2->isChecked() == true && ui->radioButton_3->isChecked() == false){
        char buff[200];
        sprintf(buff, "UPDATE customer_information SET room = '1' WHERE identifyNumber = '%s'", dataIdC);
       if (mysql_query(conect, buff)) {
            //ui->label->setText("Hata");
       }
    }
    if (ui->radioButton_3->isChecked() == false && ui->radioButton_2->isChecked() == false && ui->radioButton_3->isChecked() == true){
        char buff[200];
        sprintf(buff, "UPDATE customer_information SET room = '2' WHERE identifyNumber = '%s'", dataIdC);
        if (mysql_query(conect, buff)) {
           //ui->label->setText("Hata");
        }
    }

    ui->pushButton_2->setEnabled(false);
}


void Rooms::on_pushButton_clicked()
{
    close();
}
