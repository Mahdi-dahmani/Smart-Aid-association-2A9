#ifndef FARAH_H
#define FARAH_H
#include "depense.h"
#include <QMainWindow>
#include <necessiteux.h>
#include "avis.h"
#include "arduino.h"
namespace Ui {
class farah;
}

class farah : public QMainWindow
{
    Q_OBJECT

public:
    explicit farah(QWidget *parent = nullptr);
    ~farah();
private slots:
    void on_pushButton_4_clicked();


    void on_pushButton_7_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_clicked();

    void on_excel_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();
    void on_pushButton_12_clicked();
void update_label();

void on_forward_clicked();

void on_forward_released();

void on_left_clicked();

void on_left_released();

void on_back_clicked();

void on_back_released();

void on_right_clicked();

void on_right_released();
void on_art_clicked();
private:
    Ui::farah *ui;
    NECESSITEUX nes;
     Depense *de;
    avis A;
    Arduino ar;
    QByteArray data;
};

#endif // FARAH_H
