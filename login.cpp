#include "login.h"
#include "ui_login.h"
#include <string.h>
#include <string>
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "arduino.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
using namespace std;
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
   QString email= ui->email->text();
   QString mdp= ui->mdp->text();
   QSqlQuery q;
   q.prepare("Select *from Membres where email_membre=:email");
   q.bindValue(":email",email);
   q.exec();
   q.first();
   if (q.first())
   {
       if (q.value(5)==mdp)
       {
           if (q.value(7)=="Event")
          { QMessageBox::information(nullptr, QObject::tr("OK"),
                                    QObject::tr("Welcome!Event departement"), QMessageBox::Cancel);}
          else if (q.value(7)=="Don")
          { QMessageBox::information(nullptr, QObject::tr("OK"),
                                    QObject::tr("Welcome!Donateur departement"), QMessageBox::Cancel);}
          else if (q.value(7)=="Depense")
          { QMessageBox::information(nullptr, QObject::tr("OK"),
                                    QObject::tr("Welcome! Depense departement"), QMessageBox::Cancel);}
          else if (q.value(7)=="Sponsor")
          { QMessageBox::information(nullptr, QObject::tr("OK"),
                                    QObject::tr("Welcome! Sponsor departement"), QMessageBox::Cancel);}
       }
       else
       {
           QMessageBox::information(nullptr, QObject::tr("OK"),
                                    QObject::tr("MDP incorrect"), QMessageBox::Cancel);
       }

   }
   else { QMessageBox::information(nullptr, QObject::tr("OK"),
                                   QObject::tr("Email incorrect"), QMessageBox::Cancel);}
}

void Login::on_pushButton_2_clicked()
{

}
void Login::update_label(){

    data=A.read_from_arduino();
    QSqlQuery q;
    q.prepare("Select * from Membres where id_membre=:email");
    qDebug() << data ;
    q.bindValue(":email",data.toInt());
    q.exec();
    q.first();
    ui->email->setText(q.value(4).toString());
    ui->mdp->setText(q.value(5).toString());
    /* if(data=="542")

      { ui->email->setText("ON"); // si les données reçues de arduino via la liaison série sont égales à 1
    // alors afficher ON
    ui->mdp->setText("carte");
    }
    else if (data=="290")

       { ui->email->setText("OFF");   // si les données reçues de arduino via la liaison série sont égales à 0
     //alors afficher ON
    ui->mdp->setText("5omsa");}*/

}
