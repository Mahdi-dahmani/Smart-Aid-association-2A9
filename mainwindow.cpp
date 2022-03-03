#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "evenement.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel( Event.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
   QString id=ui->lineEditID->text();
   QString nom=ui->lineEditnom->text();
   QString date=ui->date->text();
   QString local=ui->local->text();
   QString budget=ui->lineEditbudget->text();
   EVENEMENT e(id,nom,date,local,budget);
   e.ajouter();
   ui->tableView->setModel( Event.afficher());

}

void MainWindow::on_pushButton_4_clicked()
{
    QString id=ui->lineEdit_supp->text();
    EVENEMENT e;
    e.supprimer(id);
    ui->tableView->setModel( Event.afficher());

}











void MainWindow::on_pushButton_3_clicked()
{
    QString nom=ui->nom->text();
    QString id=ui->id->text();
    QString date=ui->EditDate->text();
    QString local=ui->Editlocal->text();
    QString budget=ui->Editbudget->text();

    EVENEMENT e(nom,id,date,local,budget);
    bool test=e.modifier(id);
    if(test)
    {
    ui->tableView->setModel(Event.afficher());
QMessageBox::information(nullptr,QObject::tr("ok"),
                         QObject::tr("Edit done"),QMessageBox::Yes);

    }
else
    {
        QMessageBox::critical(nullptr,QObject::tr("ok"),
                              QObject::tr("Edit impossible"),QMessageBox::Yes);


    }



}
