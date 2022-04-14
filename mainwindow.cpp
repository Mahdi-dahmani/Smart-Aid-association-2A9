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
#include "form.h"
#include "ui_form.h"
#include <ActiveQt/qaxobject.h>
#include <ActiveQt/qaxbase.h>
#include <QMessageBox>
#include <qstring.h>
#include "excelexporthelper.h"
#include <QFile>
#include <stdexcept>
#include "form2.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    ui->tableView->setModel(mem.afficher());
    ui->p_nom->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    ui->p_id->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    ui->p_prenom->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    ui->p_user->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
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

void MainWindow::on_p_nom_clicked()
{
    QSqlQueryModel  * mod=new QSqlQueryModel();
    mod->setQuery("SELECT * FROM Membres Order by nom_membre ASC ");
    mod->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    mod->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    mod->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    mod->setHeaderData(3,Qt::Horizontal,QObject::tr("User"));
    mod->setHeaderData(4,Qt::Horizontal,QObject::tr("Email"));
    mod->setHeaderData(5,Qt::Horizontal,QObject::tr("MDP"));
     mod->setHeaderData(6,Qt::Horizontal,QObject::tr("NB_POINT"));
    mod->setHeaderData(7,Qt::Horizontal,QObject::tr("Branche"));

   ui->tableView->setModel(mod);

}

void MainWindow::on_p_id_clicked()
{
    QSqlQueryModel  * mod=new QSqlQueryModel();
    mod->setQuery("SELECT * FROM Membres Order by id_membre ASC ");
    mod->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    mod->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    mod->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    mod->setHeaderData(3,Qt::Horizontal,QObject::tr("User"));
    mod->setHeaderData(4,Qt::Horizontal,QObject::tr("Email"));
    mod->setHeaderData(5,Qt::Horizontal,QObject::tr("MDP"));
     mod->setHeaderData(6,Qt::Horizontal,QObject::tr("NB_POINT"));
    mod->setHeaderData(7,Qt::Horizontal,QObject::tr("Branche"));

   ui->tableView->setModel(mod);
}

void MainWindow::on_pushButton_7_clicked()
{
Form *f =new Form();
f->show();

}

void MainWindow::on_p_prenom_clicked()
{
    QSqlQueryModel  * mod=new QSqlQueryModel();
    mod->setQuery("SELECT * FROM Membres Order by prenom_membre ASC ");
    mod->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    mod->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    mod->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    mod->setHeaderData(3,Qt::Horizontal,QObject::tr("User"));
    mod->setHeaderData(4,Qt::Horizontal,QObject::tr("Email"));
    mod->setHeaderData(5,Qt::Horizontal,QObject::tr("MDP"));
    mod->setHeaderData(6,Qt::Horizontal,QObject::tr("NB_POINT"));
    mod->setHeaderData(7,Qt::Horizontal,QObject::tr("Branche"));

   ui->tableView->setModel(mod);
}

void MainWindow::on_p_user_clicked()
{
    QSqlQueryModel  * mod=new QSqlQueryModel();
    mod->setQuery("SELECT * FROM Membres Order by username_membre ASC ");
    mod->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    mod->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    mod->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    mod->setHeaderData(3,Qt::Horizontal,QObject::tr("User"));
    mod->setHeaderData(4,Qt::Horizontal,QObject::tr("Email"));
    mod->setHeaderData(5,Qt::Horizontal,QObject::tr("MDP"));
     mod->setHeaderData(6,Qt::Horizontal,QObject::tr("NB_POINT"));
    mod->setHeaderData(7,Qt::Horizontal,QObject::tr("Branche"));

   ui->tableView->setModel(mod);

}

void MainWindow::on_excel_clicked()
{
    try
        {
            const QString fileName = "c:\test.xlsx";

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

void MainWindow::on_pushButton_7_clicked(bool checked)
{

}

void MainWindow::on_mdm_clicked()
{
    Form2 *f =new Form2();
    f->show();
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->tableView->setModel(mem.afficher());
    ui->rech->setText("");
}
