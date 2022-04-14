#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "arduino.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void update_label();
private:
    Ui::Login *ui;
    QByteArray data; // variable contenant les données reçues

    Arduino A; // objet temporaire
};

#endif // LOGIN_H
