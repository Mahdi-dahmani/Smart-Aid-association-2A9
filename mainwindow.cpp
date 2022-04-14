#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "evenement.h"
#include <QString>
#include <ActiveQt/qaxobject.h>
#include <ActiveQt/qaxbase.h>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QFile>
#include <stdexcept>
#include <QMessageBox>
#include "excelexporthelper.h"
#include "form.h"
#include "avis.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel( Event.afficher());
    ui->tableView_2->setModel( A.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
   QString id=ui->lineEditID->text();
   QString nom=ui->lineEditnom->currentText();
   QString date=ui->date->text();
   QString local=ui->local->text();
   QString budget=ui->lineEditbudget->text();
   EVENEMENT e(id,nom,date,local,budget);
   bool test=e.ajouter();


  if(test)
   {
      ui->tableView->setModel( Event.afficher());
   QMessageBox::information(nullptr,QObject::tr("ok"),
                            QObject::tr("Ajout done"),QMessageBox::Yes);

       }
   else
       {
           QMessageBox::critical(nullptr,QObject::tr("ok"),
                                 QObject::tr("Ajout impossible"),QMessageBox::Yes);

}
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
    QString nom=ui->nom_2->currentText();
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

void MainWindow::on_pushButton_5_clicked()
{
    QString val=ui->line_recherche->text();
         if((val!=""))
     {        ui->tableView->setModel(Event.rechercher(val));
         }
}

void MainWindow::on_pushButton_6_clicked()
{

    QSqlQueryModel * modell=new QSqlQueryModel();

    modell->setQuery("SELECT * FROM EVENEMENT  ORDER BY  NOM_EVENT ASC ");
    ui->tableView->setModel(modell);

}

void MainWindow::on_excel_clicked()
{
    try
            {
                const QString fileName = "c:\\test.xlsx";

                ExcelExportHelper helper;
    int l=2;
                QSqlQuery q;
                if(q.exec("SELECT * FROM evenement"))
                {
    helper.SetCellValue(1,1,"ID_EVENT");
    helper.SetCellValue(1,2,"NOM_EVENT");
    helper.SetCellValue(1,3,"DATE_EVENT");
    helper.SetCellValue(1,4,"LOCALISATION");
    helper.SetCellValue(1,5,"BUDGET_EVENT");
    helper.SetCellValue(1,6,"NB_POINT");

                    while (q.next())
                    {

                helper.SetCellValue(l,1,q.value(0).toString());
                helper.SetCellValue(l,2,q.value(1).toString());
                helper.SetCellValue(l,3,q.value(2).toString());
                helper.SetCellValue(l,4,q.value(3).toString());
                helper.SetCellValue(l,5,q.value(4).toString());
                helper.SetCellValue(l,6,q.value(5).toString());
                helper.SetCellValue(l,7,q.value(6).toString());
                helper.SetCellValue(l,8,q.value(7).toString());
    l++;

                    }
                helper.SaveAs(fileName);
            }}
            catch (const exception& e)
            {
                QMessageBox::critical(this, "Error - Demo", e.what());
            }
}

void MainWindow::on_pushButton_7_clicked()
{
    Form *f= new Form();
    f->show();
}







void MainWindow::on_pushButton_9_clicked()
{ bool test;
    QString id=ui->id_2->text();
       QString id_event=ui->id_event->text();
       QString description=ui->desc->text();
       QString nb_point=ui->nb_point->text();

       avis A(id,id_event,description,nb_point);
      test=A.ajouter1();


      if(test)
       {
          ui->tableView_2->setModel( A.afficher());
       QMessageBox::information(nullptr,QObject::tr("ok"),
                                QObject::tr("Ajout done"),QMessageBox::Yes);

           }
       else

               QMessageBox::critical(nullptr,QObject::tr("ok"),
                                     QObject::tr("Ajout impossible"),QMessageBox::Yes);


    }


//void MainWindow::on_pushButton_11_clicked()
//{
   // QString id=ui->id_supp->text();
   // avis A;
   // A.supprimer(id);
  //  ui->tableView_2->setModel( Event.afficher());

//}
