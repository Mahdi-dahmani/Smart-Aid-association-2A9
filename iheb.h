#ifndef IHEB_H
#define IHEB_H


#include <arduino.h>
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include "depense.h"
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QModelIndex>
#include "avis.h"
namespace Ui {
class iheb;
}

class iheb : public QMainWindow
{
    Q_OBJECT

public:
    explicit iheb(QWidget *parent = nullptr);
    ~iheb();
private slots:


void on_suprim_clicked();

void on_pushButton_6_clicked();

void on_search_clicked();

void on_pushButton_4_clicked();


 void on_img_clicked();





 void on_pushButton_5_clicked();

// void on_tabdepense1_activated(const QModelIndex &index);

 void on_tabdepense1_clicked(const QModelIndex &index);

 void on_pushButton_7_clicked();

 void on_statsbuttton_clicked();

 void on_pushButton_8_clicked();

 void on_pushButton_web_clicked();



 void on_pushButton_2_clicked();

 //void on_pushButton_9_clicked();

 void on_arduino_clicked();
void update_label();
void on_pushButton_11_clicked();

private:
    Ui::iheb *ui;
    QString textvalue;
    Depense *de;
QSqlTableModel  *model;
QByteArray data; // variable contenant les données reçues
avis ar;
    Arduino A;
};

#endif // IHEB_H
