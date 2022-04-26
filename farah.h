#ifndef FARAH_H
#define FARAH_H

#include <QMainWindow>
#include <necessiteux.h>
#include "avis.h"
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

private:
    Ui::farah *ui;
    NECESSITEUX nes;
    avis A;
};

#endif // FARAH_H
