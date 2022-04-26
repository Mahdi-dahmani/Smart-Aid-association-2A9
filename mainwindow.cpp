#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "necessiteux.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <ActiveQt/qaxobject.h>
#include <ActiveQt/qaxbase.h>
#include <QMessageBox>
#include <QIntValidator>
#include "excelexporthelper.h"
#include <QFile>
#include <stdexcept>
#include <QWidget>
#include <QWidgetAction>
#include <form.h>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->age->setValidator(new QIntValidator(0, 9999999, this));
    ui->id->setValidator(new QIntValidator(0, 9999999, this));
    ui->tel->setValidator(new QIntValidator(0, 9999999, this));
    ui->tableView->setModel(nes.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_4_clicked()
{
    QString id=ui->id->text();
    QString nom=ui->nom->text();
    QString sexe=ui->sexe->text();
    QString age=ui->age->text();
    QString tel=ui->tel->text();
    QString adresse=ui->adresse->text();
    QString besoin=ui->besoin->currentText();
    QString mbr=ui->mbr->text();
    QString date=ui->date->text();

    NECESSITEUX e(id,nom,sexe,age,tel,adresse,besoin,mbr,date);
    if (nom.isEmpty()||adresse.isEmpty()||id==0)
    {
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                 QObject::tr("Case Obligatoire!\n"),QMessageBox::Cancel );
    }
    else
        if(!(nom.contains(QRegExp("^[A-Za-z]+$"))))
                {

                    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                             QObject::tr("Veuillez entrer une chaine!\n"
                                                         "Click Cancel to exit. "),QMessageBox::Cancel);

                }
        else
            if (sexe!= "femme" && sexe !="homme" && sexe != sexe.isEmpty())
                    {

                        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                                 QObject::tr("Veuillez entrer homme ou femme!\n"
                                                             "Click Cancel to exit. "),QMessageBox::Cancel);

                    }

    else
        {
            e.ajouter();
            ui->tableView->setModel(nes.afficher());

        }

}










void MainWindow::on_pushButton_7_clicked()
{

    QString id=ui->lineEdit_supp->text();
    NECESSITEUX e ;
    e.supprimer(id);

    ui->tableView->setModel(nes.afficher());
}


void MainWindow::on_pushButton_2_clicked()
{
    QString id=ui->lineEdit->text();
    QString nom=ui->lineEdit_2->text();
    QString sexe=ui->lineEdit_3->text();
    QString age=ui->lineEdit_4->text();
    QString tel=ui->lineEdit_5->text();
    QString adresse=ui->lineEdit_6->text();
    QString besoin=ui->besoin->currentText();
    QString mbr=ui->spinBox->text();

    QString date=ui->dateEdit->text();

    NECESSITEUX e(id,nom,sexe,age,tel,adresse,besoin,mbr,date);
    ui->age->setValidator(new QIntValidator(0, 9999999, this));
    ui->id->setValidator(new QIntValidator(0, 9999999, this));
    ui->tel->setValidator(new QIntValidator(0, 9999999, this));

        if(!(nom.contains(QRegExp("^[A-Za-z]+$||nom.isEmpty()"))))
                {

                    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                             QObject::tr("Veuillez entrer une chaine!\n"
                                                         "Click Cancel to exit. "),QMessageBox::Cancel);

                }

        else{
            bool test = e.modifier(id);
            if (test)
            {
               ui->tableView->setModel(nes.afficher());
               QMessageBox::information(nullptr,QObject::tr("OK"),
                                        QObject::tr("Edit done"),QMessageBox::Cancel );
            }
            else
            {
                QMessageBox::critical(nullptr , QObject::tr("OK"),
                                      QObject::tr("Edit impossible") , QMessageBox::Cancel );
            }
        }

        }


void MainWindow::on_pushButton_8_clicked()
{
    QString nom =ui->lineEdit_9->text();


    if (nom!="")
        ui->tableView->setModel(nes.rechercher(nom));
    else
        ui->tableView->setModel(nes.afficher());

}

void MainWindow::on_pushButton_clicked()
{
     QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM NECESSITEUX ORDER BY MBR_FAMILLE ASC ;");
             ui->tableView->setModel(model);
}

void MainWindow::on_excel_clicked()
{
    try
            {
                const QString fileName = "c:\\test.xlsx";

                ExcelExportHelper helper;
    int l=2;
                QSqlQuery q;
                if(q.exec("SELECT * FROM NECESSITEUX"))
                {
    helper.SetCellValue(1,1,"ID_NECESSITEUX");
    helper.SetCellValue(1,2,"NOM_NECESSITEUX");
    helper.SetCellValue(1,3,"SEXE");
    helper.SetCellValue(1,4,"AGE");
    helper.SetCellValue(1,5,"TEL");
    helper.SetCellValue(1,6,"ADRESSE");
    helper.SetCellValue(1,7,"BESOIN");
    helper.SetCellValue(1,8,"MBR_FAMILLE");
    helper.SetCellValue(1,9,"DATE_NECESSITEUX");
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
                helper.SetCellValue(l,9,q.value(7).toString());
    l++;

                    }
                helper.SaveAs(fileName);
            }}
            catch (const exception& e)
            {
                QMessageBox::critical(this, "Error - Demo", e.what());
            }
}

void MainWindow::on_pushButton_5_clicked()
{
    Form *f= new Form();
        f->show();
}

void MainWindow::on_pushButton_9_clicked()
{
   /* QSqlQuery q,q1;
    q.prepare("Select distinct tel from necessiteux");
    q.exec();
    int tot[100],i=0;
    while (q.next())
    {
        q1.prepare("Select * from necessiteux where tel = :tel");
        q1.bindValue(":tel",q.value(4));
        q1.exec();
        while (q1.next())
            tot[i]++;
        i++;

    }*/
    /*QSqlQueryModel * model=new QSqlQueryModel();
        model->setQuery("Select  ID_NECESSITEUX, SEXE, TEL, count(TEL) from NECESSITEUX");

        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_NECESSITEUX"));
         model->setHeaderData(1,Qt::Horizontal,QObject::tr("SEXE"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("TEL"));*/
        /*model->setHeaderData(3,Qt::Horizontal,QObject::tr("count(TEL)"));*/
        /*model->setHeaderData(3,Qt::Horizontal,QObject::tr("AGE"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("TEL"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("ADRESSE"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("BESOIN"));
        model->setHeaderData(7,Qt::Horizontal,QObject::tr("MBR_FAMILLE"));
        model->setHeaderData(8,Qt::Horizontal,QObject::tr("DATE_NECESSITEUX"));*/
        // ui->tableView->setModel(model);
        QSqlQueryModel * modell=new QSqlQueryModel();
         modell->setQuery("Select   BESOIN, tel, count(tel) as occurence from necessiteux group by    BESOIN, tel");

        modell->setHeaderData(8,Qt::Horizontal,QObject::tr("besoin"));
         modell->setHeaderData(9,Qt::Horizontal,QObject::tr("Telephone"));
         modell->setHeaderData(10,Qt::Horizontal,QObject::tr("occurance"));
        /* model->insertColumns(9,)
         QSqlQueryModel * modelll= model + modell;*/
 ui->tableView->setModel(modell);
          /* ui->tableView->setModel(model);*/


}


void MainWindow::on_pushButton_10_clicked()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("Select * from necessiteux  order by besoin asc, age desc, MBR_FAMILLE desc");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_NECESSITEUX"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_NECESSITEUX"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("SEXE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("AGE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("TEL"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ADRESSE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("BESOIN"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("MBR_FAMILLE"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("DATE_NECESSITEUX"));
     ui->tableView->setModel(model);




}
