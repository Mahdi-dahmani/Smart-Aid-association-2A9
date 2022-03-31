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

QSqlQuery q,q1;
q1.exec("Select max(nbpoints_membre) from membres");
q1.first();
q.prepare("Select * from membres where nbpoints_membre= :val");
q.bindValue(":val",q1.value(0).toString());
q.exec();
q.next();
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
