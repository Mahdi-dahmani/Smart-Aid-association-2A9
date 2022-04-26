#include "form2.h"
#include "ui_form2.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <string>
#include <QDebug>
using namespace std;
Form2::Form2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form2)
{
    ui->setupUi(this);
QSqlQuery b,b1,b2,b3;
    b.exec("Select id_event,nb_point from evenement");
    while (b.next()){
    b1.prepare("select * from MM where id_event = :id ");
    b1.bindValue(":id",b.value(0));
    b1.exec();
    while (b1.next()){
    b2.prepare("update membres set nbpoints_membre=nbpoints_membre + :nb where id_membre = :idd");
    b2.bindValue(":nb",b.value(1).toInt());
    b2.bindValue(":idd",b1.value(0).toString());
    b2.exec();
    }
    }


QSqlQuery q,q1;
q1.exec("Select MAX(nbpoints_membre) from membres");
q1.first();
q.prepare("Select * from membres where nbpoints_membre= :val");
q.bindValue(":val",q1.value(0).toString());
q.exec();
q.first();
qDebug() << q1.value(0).toString();
qDebug() << q.value(1).toString();
ui->nom->setText(q.value(1).toString());
ui->prenom->setText(q.value(2).toString());
ui->nb->setText(q.value(6).toString());
}

Form2::~Form2()
{
    delete ui;
}
