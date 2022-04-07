#include "login.h"
#include "ui_login.h"
#include <string.h>
#include <string>
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
using namespace std;
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
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
