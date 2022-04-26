#ifndef MAISSA_H
#define MAISSA_H

#include <QMainWindow>
#include <evenement.h>
#include <avis.h>
#include <arduino.h>
namespace Ui {
class maissa;
}

class maissa : public QMainWindow
{
    Q_OBJECT

public:
    explicit maissa(QWidget *parent = nullptr);
    ~maissa();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();



    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_excel_clicked();

    void on_pushButton_7_clicked();



    void on_pushButton_9_clicked();



    void on_pushButton_8_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_14_clicked();
    void update_label();

    void on_pushButton_8_pressed();

    void on_pushButton_8_released();

    void on_pushButton_13_pressed();

    void on_pushButton_13_released();

    void on_pushButton_12_pressed();

    void on_pushButton_12_released();

    void on_pushButton_14_pressed();

    void on_pushButton_14_released();

    void on_map_clicked();
    void on_pushButton_11_clicked();

    void on_pushButton_15_clicked();

private:
    Ui::maissa *ui;
    EVENEMENT Event;
    avis A;
    Arduino ar;
    QByteArray data;
};

#endif // MAISSA_H
