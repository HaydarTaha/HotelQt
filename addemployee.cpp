#include "addemployee.h"
#include "ui_addemployee.h"
#include </opt/homebrew/Cellar/mysql/8.0.30_1/include/mysql/mysql.h>


MYSQL *con2 = mysql_init(NULL);

AddEmployee::AddEmployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEmployee)
{
    ui->setupUi(this);
    if (con2 == NULL){
            ui->label_5->setText("MySql bağlantı Hatası");
            exit(1);
        }
    if (mysql_real_connect(con2, "localhost", "root", "Tahatunc2142",
              "hotel", 0, NULL, 0) == NULL)
      {
          //finish_with_error(con);
        ui->label_5->setText("Hata");
      }
}

AddEmployee::~AddEmployee()
{
    delete ui;
}

void AddEmployee::on_pushButton_clicked()
{
    emplyeeNumber = new EmplyeeNumber(this);
    emplyeeNumber->show();
}


void AddEmployee::on_pushButton_2_clicked()
{
 QString name = ui->lineEdit->text();
 QString day = ui->lineEdit_3->text();
 QString department = ui->lineEdit_2->text();

 std::string nameStd = name.toStdString();
 const char* nameC = nameStd.c_str();

 std::string departmentStd = department.toStdString();
 const char* departmentC = departmentStd.c_str();

 std::string dayStd = day.toStdString();
 const char* dayC = dayStd.c_str();

 char buff[400];
 sprintf(buff,"INSERT INTO employee_t (name, employee_type, day) VALUES('%s', '%s', '%s')", nameC, departmentC, dayC);

 if (mysql_query(con2, buff)) {
     ui->label_5->setText("Hata");
 } else {
         ui->label_5->setText("Bilgiler Başarıyla Kaydedildi.");
         ui->lineEdit->setText("");
         ui->lineEdit_2->setText("");
         ui->lineEdit_3->setText("");
 }
}

