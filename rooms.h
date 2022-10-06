#ifndef ROOMS_H
#define ROOMS_H

#include <QDialog>
#include <QPixmap>

namespace Ui {
class Rooms;
}

class Rooms : public QDialog
{
    Q_OBJECT

public:
    explicit Rooms(QWidget *parent = nullptr);
    ~Rooms();


private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

public slots:
    void identify(QString dataId);

private:
    Ui::Rooms *ui;
};

#endif // ROOMS_H
