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
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QDebug>
#include <qdebug.h>
QT_CHARTS_USE_NAMESPACE
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    int ret=ar.connect_arduino(); // lancer la connexion à arduino
         switch(ret){
         case(0):qDebug()<< "arduino is available and connected to : "<< ar.getarduino_port_name();
             break;
         case(1):qDebug() << "arduino is available but not connected to :" <<ar.getarduino_port_name();
            break;
         case(-1):qDebug() << "arduino is not available";
         }
          QObject::connect(ar.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
    ui->tableView->setModel(mem.afficher());
    QSqlQueryModel  *model = new QSqlQueryModel();
    model->setQuery("select id_event, nom_event from evenement");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_event"));

    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom_event"));

ui->tableView_2->setModel(model);
    ui->p_nom->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    ui->p_id->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    ui->p_prenom->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    ui->p_user->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    QSqlQuery q,q1,q2,q3,q4,q5;
    q.exec("Select * from membres");
    int tot=0;
    while (q.next())
        tot++;
   qDebug() << "total =" << tot;
    q1.prepare("Select * from membres where BRANCHE_MEMBRE = :nom ");
    q1.bindValue(":nom","Don");
    q1.exec();
    int tot_don=0;
    while (q1.next())
        tot_don++;
 qDebug() << "pourcentage don =" << tot_don;
    qreal pour_don=(tot_don*100)/tot;

    q2.prepare("Select * from membres where BRANCHE_MEMBRE = :nom ");
    q2.bindValue(":nom","Event");
    q2.exec();
    int tot_event=0;
    while (q2.next())
        tot_event++;

    qreal pour_event=(tot_event*100)/tot;

    q3.prepare("Select * from membres where BRANCHE_MEMBRE = :nom ");
    q3.bindValue(":nom","Depense");
    q3.exec();
    int tot_dep=0;
    while (q3.next())
        tot_dep++;
    qreal pour_dep=(tot_dep*100)/tot;

    q4.prepare("Select * from membres where BRANCHE_MEMBRE = :nom ");
    q4.bindValue(":nom","Sponsor");
    q4.exec();
    int tot_spon=0;
    while (q4.next())
        tot_spon++;
    qreal pour_spon=(tot_spon*100)/tot;

    q5.prepare("Select * from membres where BRANCHE_MEMBRE = :nom ");
    q5.bindValue(":nom","Necissiteux");
    q5.exec();
    int tot_ne=0;
    while (q5.next())
        tot_ne++;
    qreal pour_ne=(tot_ne*100)/tot;

    QPieSeries *series = new QPieSeries();
     series->append("Donateur",pour_don);
     series->append("Depenses",pour_dep);
     series->append("Neccisiteux",pour_ne);
     series->append("Event",pour_event);
     series->append("Sponsors",pour_spon);
     QPieSlice *slice0= series->slices().at(0);
     slice0->setLabelVisible();
     QPieSlice *slice1 = series->slices().at(1);

     slice1->setLabelVisible();

     slice1->setBrush(Qt::green);

     QPieSlice *slice2= series->slices().at(2);
     slice2->setLabelVisible();
      slice2->setBrush(Qt::red);
     QPieSlice *slice3= series->slices().at(3);
     slice3->setLabelVisible();
      slice3->setBrush(Qt::yellow);
     QPieSlice *slice4= series->slices().at(4);
     slice4->setLabelVisible();
      slice4->setBrush(Qt::blue);
     QChart *chart = new QChart();
     chart->addSeries(series);
     chart->setTitle("Membre pour chaque departement");
     chart->legend()->hide();

     QChartView *chartview = new QChartView(chart,ui->widget);
     chartview->resize(500,400);
     chartview->setRenderHint(QPainter::Antialiasing);
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
    bool test;
        qDebug()<< "done";
        QString id=ui->id_2->text();
           QString id_event=ui->id_event->text();
           QString description=ui->desc->text();
           QString nb_point=ui->nb_point->text();

           avis A(id,id_event,description,nb_point);
          test=A.ajouter1();


          if(test)
           {
              int tot=0,i=0,nb;

           QMessageBox::information(nullptr,QObject::tr("ok"),
                                    QObject::tr("Ajout done"),QMessageBox::Yes);

           QSqlQuery q1,q2,q3;
           q1.exec("select id_event from evenement");
           while (q1.next()){
               tot=0;
               i=0;
               nb=0;
            q2.prepare("Select * from aviss where id_event = :id");
            q2.bindValue(":id",q1.value(0).toString());
             q2.exec();
             while (q2.next()){

                 tot=tot+q2.value(3).toInt();
                 i++;
             }
             nb=tot/i;
             q3.prepare("update evenement set nb_point=nb_point + :nb where id_event = :idd");
             q3.bindValue(":nb",nb);
             q3.bindValue(":idd",q1.value(0).toString());
             q3.exec();

       }


















               }
           else

                   QMessageBox::critical(nullptr,QObject::tr("ok"),
                                         QObject::tr("Ajout impossible"),QMessageBox::Yes);






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

void MainWindow::on_pushButton_9_clicked()
{
     delete ui;
}

void MainWindow::on_art_clicked()
{
    ar.write_to_arduino("2");
    QSqlQuery q;
    q.prepare("INSERT INTO ALARM (ID,DATEE) VALUES (ALARM_SEQ.nextval,sysdate)");
    q.exec();

ui->etat->setText("Arreter");
}
void MainWindow::update_label()
{
    data=ar.read_from_arduino();

    if(data=="1")
        ui->etat->setText("Mouvement"); // si les données reçues de arduino via la liaison série sont égales à 1
    // alors afficher ON

    else if (data=="0")

        ui->etat->setText("Pas de mouvement");   // si les données reçues de arduino via la liaison série sont égales à 0
     //alors afficher ON
}

void MainWindow::on_pushButton_11_clicked()
{
    QSqlQuery q;
    q.prepare("DELETE * FROM MM");
    q.exec();
    q.prepare("update membres set nbpoints_membre = 0");
    q.exec();
}
