#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "membre.h"
#include<string>
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
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
    QString nb_point=QString::number(nb);
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString email=ui->lineEdit_email->text();
    QString user=ui->lineEdit_user->text();
    QString mdp=ui->lineEdit_mdp->text();
    QString branche=ui->lineEdit_branche->text();
    Membre m(id,nom,prenom,user,email,mdp,branche,nb_point);
    bool test = m.ajouter();
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
