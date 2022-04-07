#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sponsor1.h"
#include <QString>
#include<QMessageBox>
#include <QApplication>
#include <QWidget>
#include <QWidgetAction>
#include "form.h"
#include <stdexcept>
#include "excelexporthelper.h"
#include "historique.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_dial_2_valueChanged(int value)
{
    ui->lcdnumber_2->display(value);
}

void MainWindow::on_ajouter_clicked()
{
    QString IDENTIFIANT_SPONSOR=ui->identifiant->text();
    QString NOM_SPONSOR=ui->nom->text();
    QString PRENOM_SPONSOR=ui->prenom->text();
    QString EMAIL_SPONSOR=ui->email->text();
    QString NUM_TEL_SPONSOR=ui->numtel->text();
    QString ADRESSE_SPONSOR=ui->adresse_2->text();
    QString  DATE_DEBUT_SPONSOR=ui->date_2->text();
    int MONTANT_SPONSOR=ui->lcdnumber_2->intValue();

    Sponsor1 s(IDENTIFIANT_SPONSOR,NOM_SPONSOR,PRENOM_SPONSOR,EMAIL_SPONSOR, NUM_TEL_SPONSOR, ADRESSE_SPONSOR,DATE_DEBUT_SPONSOR,MONTANT_SPONSOR);


    bool test=s.ajouter();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("cajouter successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
ui->tableView->setModel( spon.afficher());
QString operation="Ajout";
historique h(operation,IDENTIFIANT_SPONSOR,NOM_SPONSOR);
 h.Ajouter();
 ui->tableView_2->setModel(h.afficher());


}
    else
        QMessageBox::critical(nullptr, QObject::tr("ajouter failed. "),
                    QObject::tr(" nn vide \n ilfaux id numéro\n il faux saisir Nom_sponsor Prenom_sponsor sans caractére spéciaux\n montant>0"
                                "Click Cancel to exit."), QMessageBox::Cancel);


}


void MainWindow::on_Supprimer_clicked()
{
    QString id=ui->identifiant->text();
        Sponsor1 s;
        s.supprimer(id);
        ui->tableView->setModel( spon.afficher());
        QString operation="supprimer";
        historique h(operation,id,"NOM_SPONSOR");
         h.Ajouter();
         ui->tableView_2->setModel(h.afficher());
}

void MainWindow::on_afficher_clicked()
{
    QSqlQueryModel * model =new QSqlQueryModel();
    QString option=ui->option->currentText();
     if(option=="Id")
 {       model->setQuery("SELECT * FROM SPONSOR  ORDER BY IDENTIFIANT_SPONSOR ASC ;");
         ui->tableView->setModel(model);
     }


else if(option=="Nom")
{
         model->setQuery("SELECT * FROM SPONSOR  ORDER BY IDENTIFIANT_SPONSOR ASC ;");
                  ui->tableView->setModel(model);
}
else if(option=="Prenom")
{
         model->setQuery("SELECT * FROM SPONSOR  ORDER BY PRENOM_SPONSOR ASC ;");
                  ui->tableView->setModel(model);
}else if(option=="Email")
{
         model->setQuery("SELECT * FROM SPONSOR  ORDER BY EMAIL_SPONSOR ASC ;");
                  ui->tableView->setModel(model);
}
else if(option=="Adresse")
     {
         model->setQuery("SELECT * FROM SPONSOR  ORDER BY ADRESSE_SPONSOR ASC ;");
                  ui->tableView->setModel(model);
     }
else if(option=="NumTel")
     {
         model->setQuery("SELECT * FROM SPONSOR  ORDER BY NUM_TEL_SPONSOR ASC ;");
                  ui->tableView->setModel(model);
     }
else if(option=="Datee")
     {
         model->setQuery("SELECT * FROM SPONSOR  ORDER BY DATE_DEBUT_SPONSOR ASC ;");
                  ui->tableView->setModel(model);
     }
     else if(option=="Montant")
          {
         model->setQuery("SELECT * FROM SPONSOR  ORDER BY MONTANT_SPONSOR ASC ;");
                  ui->tableView->setModel(model);
          }
     else ui->tableView->setModel( spon.afficher());
}
void MainWindow::on_Modifier_clicked()
{


    QString id=ui->identifiant->text();
    QString nom_sponsor=ui->nom->text();
    QString prenom_sponsor=ui->prenom->text();
    QString email_sponsor=ui->email->text();
    QString num_tel_sponsor=ui->numtel->text();
    QString adresse_sponsor=ui->adresse_2->text();
    QString  date_sponsor=ui->date_2->text();
    int montant_sponsor=ui->lcdnumber_2->intValue();

    Sponsor1 s(nom_sponsor,prenom_sponsor,email_sponsor,num_tel_sponsor,adresse_sponsor,date_sponsor,montant_sponsor);
        bool test=s.modifier(id);
        if(test)
        {
        ui->tableView->setModel(spon.afficher());
    QMessageBox::information(nullptr,QObject::tr("ok"),
                             QObject::tr("Edit done"),QMessageBox::Yes);
    QString operation="modifier";
    historique h(operation,id,nom_sponsor);
     h.Ajouter();
     ui->tableView_2->setModel(h.afficher());

        }
    else
        {
            QMessageBox::critical(nullptr, QObject::tr("ajouter failed. "),
                        QObject::tr(" nn vide \n ilfaux id numéro\n il faux saisir Nom_sponsor Prenom_sponsor sans caractére spéciaux\n montant>0"
                                    "Click Cancel to exit."), QMessageBox::Cancel);


        }
        ui->tableView->setModel( spon.afficher());
}







void MainWindow::on_identifiant_editingFinished()
{

    QString val=ui->identifiant->text();
    QString option=ui->option->currentText();
     if((val!="")&&(option=="Id"))
 {        ui->tableView->setModel(spon.afficher_recherche0(val));

     }
     else if((val!="")&&(option=="Nom"))
     {
        ui->tableView->setModel(spon.afficher_recherche2(val));
     }
     else if((val!="")&&(option=="Prenom"))
     {
         ui->tableView->setModel(spon.afficher_recherche3(val));
     }else if((val!="")&&(option=="Email"))
     {
         ui->tableView->setModel(spon.afficher_recherche4(val));
     }
     else if((val!="")&&(option=="Adresse"))
          {
              ui->tableView->setModel(spon.afficher_recherche1(val));
          }
     else if((val!="")&&(option=="NumTel"))
          {
              ui->tableView->setModel(spon.afficher_recherche5(val));
          }
     else if((val!="")&&(option=="Datee"))
          {
              ui->tableView->setModel(spon.afficher_recherche6(val));
          }
     else

     {
         ui->tableView->setModel(spon.afficher_recherche7(val));

     }
}






void MainWindow::on_afficher_2_clicked()
{
    QSqlQueryModel * model =new QSqlQueryModel();
    QString option=ui->option->currentText();
     if(option=="Id")
 {       model->setQuery("SELECT * FROM SPONSOR  ORDER BY IDENTIFIANT_SPONSOR DESC ;");
         ui->tableView->setModel(model);
     }


else if(option=="Nom")
{
         model->setQuery("SELECT * FROM SPONSOR  ORDER BY IDENTIFIANT_SPONSOR DESC ;");
                  ui->tableView->setModel(model);
}
else if(option=="Prenom")
{
         model->setQuery("SELECT * FROM SPONSOR  ORDER BY PRENOM_SPONSOR DESC ;");
                  ui->tableView->setModel(model);
}else if(option=="Email")
{
         model->setQuery("SELECT * FROM SPONSOR  ORDER BY EMAIL_SPONSOR DESC ;");
                  ui->tableView->setModel(model);
}
else if(option=="Adresse")
     {
         model->setQuery("SELECT * FROM SPONSOR  ORDER BY ADRESSE_SPONSOR DESC ;");
                  ui->tableView->setModel(model);
     }
else if(option=="NumTel")
     {
         model->setQuery("SELECT * FROM SPONSOR  ORDER BY NUM_TEL_SPONSOR DESC ;");
                  ui->tableView->setModel(model);
     }
else if(option=="Datee")
     {
         model->setQuery("SELECT * FROM SPONSOR  ORDER BY DATE_DEBUT_SPONSOR DESC ;");
                  ui->tableView->setModel(model);
     }
     else if(option=="Montant")
          {
         model->setQuery("SELECT * FROM SPONSOR  ORDER BY MONTANT_SPONSOR DESC ;");
                  ui->tableView->setModel(model);
          }
     else ui->tableView->setModel( spon.afficher());
}



void MainWindow::on_pushButton_2_clicked()
{
    Form *f= new Form();
    f->show();
}

void MainWindow::on_export_2_clicked()
{
    try
            {
                const QString fileName = "c:\\test.xlsx";

                ExcelExportHelper helper;
    int l=2;
                QSqlQuery q;
                if(q.exec("SELECT * FROM SPONSOR"))
                {

    helper.SetCellValue(1,1,"IDENTIFIANT_SPONSOR");
    helper.SetCellValue(1,2,"NOM_SPONSOR");
    helper.SetCellValue(1,3,"PRENOM_SPONSOR");
    helper.SetCellValue(1,4,"EMAIL_SPONSOR");
    helper.SetCellValue(1,5,"NUM_TEL_SPONSOR");
    helper.SetCellValue(1,6,"MONTANT_SPONSOR");

                    while (q.next())
                    {

                helper.SetCellValue(l,1,q.value(0).toString());
                helper.SetCellValue(l,2,q.value(1).toString());
                helper.SetCellValue(l,3,q.value(2).toString());
                helper.SetCellValue(l,4,q.value(3).toString());
                helper.SetCellValue(l,5,q.value(4).toString());
                helper.SetCellValue(l,6,q.value(5).toString());

    l++;

                    }
                helper.SaveAs(fileName);
            }}
    catch (const exception& e)
    {
        QMessageBox::critical(this, "Error - Demo", e.what());
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->tableView_2->setModel(h.afficher());

}
