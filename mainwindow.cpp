#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "membre.h"
#include <string.h>
#include <string>
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->tableView->setModel(mem.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int i=rand()%1000;
    QString id=QString::number(i);
    int nb=0;
    bool test;
    QString nb_point=QString::number(nb);
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString email=ui->lineEdit_email->text();
    QString user=ui->lineEdit_user->text();
    QString mdp=ui->lineEdit_mdp->text();
    QString branche=ui->lineEdit_branche->text();
    Membre m(id,nom,prenom,user,email,mdp,branche,nb_point);
    if ((m.check(nom))&&(m.check(prenom))&&(m.check_branche(branche))&&(m.check_mdp(mdp)))
    test = m.ajouter();
    else test=false;
    if (test)
    {
         ui->tableView->setModel(mem.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout done"), QMessageBox::Cancel);



    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("OK"),
                                 QObject::tr("Non"), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_2_clicked()
{



    QString user=ui->lineEdit_supp_user->text();



    bool test = mem.supprimer(user);
    if (test)
    {
         ui->tableView->setModel(mem.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression done"), QMessageBox::Cancel);



    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("OK"),
                                 QObject::tr("Membre non trouvée!!"), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_4_clicked()
{


    QString nom=ui->lineEdit_mnom->text();
    QString prenom=ui->lineEdit_mprenom->text();
    QString email=ui->lineEdit_memail->text();
    QString user=ui->lineEdit_muser->text();
    QString mdp=ui->lineEdit_mmdp->text();
    QString branche=ui->lineEdit_mbranche->text();
    Membre m(nom,prenom,user,email,mdp,branche);
    bool test = m.modifier(user);
    if (test)
    {
         ui->tableView->setModel(mem.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Edit done"), QMessageBox::Cancel);



    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("OK"),
                                 QObject::tr("Edit impossible"), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    QString nom=ui->rech->text();


    if (nom!="")
    ui->tableView->setModel(mem.rechercher(nom));
    else
         ui->tableView->setModel(mem.afficher());
}


void MainWindow::on_lineEdit_nom_editingFinished()
{
    QPalette *p= new QPalette();
    p->setColor(QPalette::Base,Qt::red);
    QString nom=ui->lineEdit_nom->text();
    string test=nom.toStdString();
    int check=0,i=0,len=test.length();
    while ((check==0)&&(i<len))
    {if (isdigit(test[i])||(islower(test[0])))
    {
        check=1;
    }
    i++;}
    if (check==1)
    {
            ui->lineEdit_nom->setPalette(*p);

    }
    else
    {
        p->setColor(QPalette::Base,Qt::white);
         ui->lineEdit_nom->setPalette(*p);
    }
}

void MainWindow::on_lineEdit_prenom_editingFinished()
{
    QPalette *p= new QPalette();
    p->setColor(QPalette::Base,Qt::red);
    QString nom=ui->lineEdit_prenom->text();
    string test=nom.toStdString();
    int check=0,i=0,len=test.length();
    while ((check==0)&&(i<len))
   {if (isdigit(test[i])||(islower(test[0])))
    {
        check=1;
    }
    i++;}
    if (check==1)
    {

       ui->lineEdit_prenom->setPalette(*p);

    }
    else
    {
        p->setColor(QPalette::Base,Qt::white);
         ui->lineEdit_prenom->setPalette(*p);
    }

}

void MainWindow::on_lineEdit_branche_editingFinished()
{
    QPalette *p= new QPalette();
    p->setColor(QPalette::Base,Qt::red);
    QString nom=ui->lineEdit_branche->text();
    string test=nom.toStdString();
    int check=0,i=0,len=test.length();
    while ((check==0)&&(i<len))
   {if (isdigit(test[i]))
    {
        check=1;
    }
    i++;}
    if (check==1)
    {

       ui->lineEdit_branche->setPalette(*p);

    }
    else
    {
        p->setColor(QPalette::Base,Qt::white);
         ui->lineEdit_branche->setPalette(*p);
    }
}

void MainWindow::on_lineEdit_mdp_editingFinished()
{
    QPalette *p= new QPalette();
    p->setColor(QPalette::Base,Qt::red);
    QString nom=ui->lineEdit_mdp->text();
    string test=nom.toStdString();

    if (test.length()<8)
    {

       ui->lineEdit_mdp->setPalette(*p);

    }
    else
    {
        p->setColor(QPalette::Base,Qt::white);
         ui->lineEdit_mdp->setPalette(*p);
    }
}

void MainWindow::on_lineEdit_user_editingFinished()
{
    QPalette *p= new QPalette();
    p->setColor(QPalette::Base,Qt::red);
    QString nom=ui->lineEdit_user->text();
    string test=nom.toStdString();

    int check=0,i=0,len=test.length();
    while ((check==0)&&(i<len))
   {if (isdigit(test[i]))
    {
        check=1;
    }
    i++;}
    if (check==1)
    {

       ui->lineEdit_user->setPalette(*p);

    }
    else
    {
        p->setColor(QPalette::Base,Qt::white);
         ui->lineEdit_user->setPalette(*p);
    }

}
void MainWindow::on_lineEdit_user_selectionChanged(){



}
