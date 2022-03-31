#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "donateurs.h"
#include <QMessageBox>
#include <QTableView>
#include <string>
#include <string.h>
#include <ActiveQt/qaxobject.h>
#include <ActiveQt/qaxbase.h>
#include <QFile>
#include <stdexcept>
#include "excelexporthelper.h"
using namespace std;
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
    bool test;
    QString ID_DONATEUR=ui->lineEdit_17->text();
    QString NOM_DONATEUR=ui->lineEdit->text();
    QString TEL_DONATEUR=ui->lineEdit_2->text();
    QString ADRESSE_DONATEUR=ui->lineEdit_3->text();
     QString DON_DONATEUR=ui->lineEdit_4->text();
    donateurs d(ID_DONATEUR,NOM_DONATEUR,TEL_DONATEUR,ADRESSE_DONATEUR,DON_DONATEUR);
    if ((d.check(NOM_DONATEUR))&&(d.check_tlf(TEL_DONATEUR)))
    test=d.ajouter();
    else {QMessageBox::information(nullptr ,QObject::tr("ok"),
                                   QObject::tr("NOM  Telephone FORMART INCORRECT\n"
                                "click cancel to exit")
                                     , QMessageBox::Cancel
                                     );
    test=false;}
    if (test)
    {
         QMessageBox::information(nullptr ,QObject::tr("ok"),
                                QObject::tr("ajout done \n"
                             "click cancel to exit")
                                  , QMessageBox::Cancel
                                  );
         ui->tableView->setModel(dtmp.afficher());
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
                                QObject::tr("suppr done \n"
                             "click cancel to exit")
                                  , QMessageBox::Cancel
                                  );
ui->tableView->setModel(dtmp.afficher());
    }
   else  QMessageBox::critical(nullptr,QObject::tr("not ok"),
                               QObject::tr("suppr non eff \n"
                                 "click cancel to exit")
                               , QMessageBox::Cancel
                               );
}

void MainWindow::on_pushButton_13_clicked()
{
    QString nom=ui->lineEdit_rech->text();


        if (nom!="")
        ui->tableView->setModel(dtmp.rechercher(nom));
        else
             ui->tableView->setModel(dtmp.afficher());

}

void MainWindow::on_pushButton_3_clicked()
{
    QString ID_DONATEUR =ui->lineEdit_16->text();
    QString NOM_DONATEUR=ui->lineEdit_nom->text();
    QString TEL_DONATEUR=ui->lineEdit_tlp->text();
    QString ADRESSE_DONATEUR=ui->lineEdit_add->text();
     QString DON_DONATEUR=ui->lineEdit_typedon->text();
donateurs d(NOM_DONATEUR,TEL_DONATEUR,ADRESSE_DONATEUR,DON_DONATEUR);
    bool test=d.modifier(ID_DONATEUR);
    if (test)
    {
        ui->tableView->setModel(dtmp.afficher());
         QMessageBox::information(nullptr ,QObject::tr("ok"),
                                QObject::tr("modif done \n"
                             "click cancel to exit")
                                  , QMessageBox::Cancel
                                  );
ui->tableView->setModel(dtmp.afficher());
    }
   else  QMessageBox::critical(nullptr,QObject::tr("not ok"),
                               QObject::tr("modiif non eff \n"
                                 "click cancel to exit")
                               , QMessageBox::Cancel
                               );

}

void MainWindow::on_trie_clicked()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT* FROM donateurs  ORDER BY id  ;");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_donateur"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Tel_donateur"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Adresse_donateur"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Don_donateur"));
             ui->tableView->setModel(model);
}

void MainWindow::on_lineEdit_editingFinished()
{

}

void MainWindow::on_excel_clicked()
{
    try
           {
               const QString fileName = "c:\\test.xlsx";

               ExcelExportHelper helper;
   int l=2;
               QSqlQuery q;
               if(q.exec("SELECT * FROM membres"))
               {
   helper.SetCellValue(1,1,"ID");
   helper.SetCellValue(1,2,"NOM");
   helper.SetCellValue(1,3,"PRENOM");
   helper.SetCellValue(1,4,"USERNAME");
   helper.SetCellValue(1,5,"EMAIL");
   helper.SetCellValue(1,6,"MDP");
   helper.SetCellValue(1,7,"NBPOINTS");
   helper.SetCellValue(1,8,"BRANCHE");
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
