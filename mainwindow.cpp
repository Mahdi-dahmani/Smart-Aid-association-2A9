#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "donateurs.h"
#include <QMessageBox>
#include <QTableView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(dtmp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString ID_DONATEUR=ui->lineEdit_17->text();
    QString NOM_DONATEUR=ui->lineEdit->text();
    QString TEL_DONATEUR=ui->lineEdit_2->text();
    QString ADRESSE_DONATEUR=ui->lineEdit_3->text();
     QString DON_DONATEUR=ui->lineEdit_4->text();
    donateurs d(ID_DONATEUR,NOM_DONATEUR,TEL_DONATEUR,ADRESSE_DONATEUR,DON_DONATEUR);
    bool test=d.ajouter();
    if (test)
    {
         QMessageBox::information(nullptr ,QObject::tr("ok"),
                                QObject::tr("ajout done \n"
                             "click cancel to exit")
                                  , QMessageBox::Cancel
                                  );
    }
   else  QMessageBox::critical(nullptr,QObject::tr("not ok"),
                               QObject::tr("ajout non eff \n"
                                 "click cancel to exit")
                               , QMessageBox::Cancel
                               );
}

void MainWindow::on_pushButton_12_clicked()
{
    QString ID_DONATEUR =ui->lineEdit_18->text();
    bool test=dtmp.supprimer(ID_DONATEUR);
    if (test)
    {
         QMessageBox::information(nullptr ,QObject::tr("ok"),
                                QObject::tr("ajout done \n"
                             "click cancel to exit")
                                  //, QMessageBox::cancel
                                  );
    }
   else  QMessageBox::critical(nullptr,QObject::tr("not ok"),
                               QObject::tr("ajout non eff \n"
                                 "click cancel to exit")
                               //, QMessageBox::cancel
                               );
}

void MainWindow::on_pushButton_13_clicked()
{


}
