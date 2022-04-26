#include "maissa.h"
#include "ui_maissa.h"
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
#include "arduino.h"
#include "avis.h"
#include <QProcess>
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
#include "connection.h"
#include "mainwindow.h"
#include "evenement.h"
QT_CHARTS_USE_NAMESPACE
using namespace std;
maissa::maissa(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::maissa)
{
    ui->setupUi(this);
    ui->tableView->setModel(Event.afficher());
    ui->tableView_2->setModel( A.afficher());
    QSqlQuery q,q1,q2,q3,q4,q5;
        q.exec("Select * from evenement");
        int tot=0;
        while (q.next())
            tot++;
       qDebug() << "total =" << tot;
        q1.prepare("Select * from evenement where  nom_event= :randonnee ");
        q1.bindValue(":randonnee","randonnee");
        q1.exec();
        int tot_randonnee=0;
        while (q1.next())
            tot_randonnee++;
     qDebug() << "pourcentage don =" << tot_randonnee;
        qreal pour_randonnee=(tot_randonnee*100)/tot;

        q2.prepare("Select * from evenement where nom_event= :collect ");
        q2.bindValue(":collect","collect");
        q2.exec();
        int tot_collect=0;
        while (q2.next())
            tot_collect++;

        qreal pour_collect=(tot_collect*100)/tot;

        q3.prepare("Select * from evenement where nom_event= :tri ");
        q3.bindValue(":tri","tri");
        q3.exec();
        int tot_tri=0;
        while (q3.next())
            tot_tri++;
        qreal pour_tri=(tot_tri*100)/tot;

        q4.prepare("Select * from evenement where nom_event= :visit ");
        q4.bindValue(":visit","visit");
        q4.exec();
        int tot_visit=0;
        while (q4.next())
            tot_visit++;
        qreal pour_visit=(tot_visit*100)/tot;
        q5.prepare("Select * from evenement where nom_event= :picnic ");
        q5.bindValue(":picnic","picnic");
        q5.exec();
        int tot_picnic=0;
        while (q5.next())
            tot_picnic++;
        qreal pour_picnic=(tot_picnic*100)/tot;






    QPieSeries *series = new QPieSeries();
     series->append("randonnee",pour_randonnee);
     series->append("collect",pour_collect);
     series->append("visit",pour_visit);
     series->append("tri",pour_tri);
     series->append("picnic",pour_picnic);

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
     chart->setTitle("les evenements les plus programmees");
     chart->legend()->hide();

     QChartView *chartview = new QChartView(chart,ui->widget);
     chartview->resize(500,400);
     chartview->setRenderHint(QPainter::Antialiasing);


}

maissa::~maissa()
{
    delete ui;
}
void maissa::on_pushButton_clicked()
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
void maissa::on_pushButton_4_clicked()
{
    QString id=ui->lineEdit_supp->text();
    EVENEMENT e;
    e.supprimer(id);
    ui->tableView->setModel( Event.afficher());

}











void maissa::on_pushButton_3_clicked()
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

void maissa::on_pushButton_5_clicked()
{
    QString val=ui->line_recherche->text();
         if((val!=""))
     {        ui->tableView->setModel(Event.rechercher(val));
         }
}

void maissa::on_pushButton_6_clicked()
{

    QSqlQueryModel * modell=new QSqlQueryModel();

    modell->setQuery("SELECT * FROM EVENEMENT  ORDER BY  NOM_EVENT ASC ");
    ui->tableView->setModel(modell);

}

void maissa::on_excel_clicked()
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

void maissa::on_pushButton_7_clicked()
{
    Form *f= new Form();
    f->show();
}







void maissa::on_pushButton_9_clicked()
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
void maissa::update_label()
{
    data=ar.read_from_arduino();
    if (data=="FFF"){
        ui->labelee->setText("FORWARD");
        QSqlQuery q;
        q.prepare("INSERT INTO CAR (ID_ACTION,DATE_ACTION,ACTION) VALUES (CAR_SEQ1.nextval,sysdate,'FORWARD')");
        q.exec();
    }
    else if (data=="RRR"){
        ui->labelee->setText("RIGHT");
        QSqlQuery q;
        q.prepare("INSERT INTO CAR (ID_ACTION,DATE_ACTION,ACTION) VALUES (CAR_SEQ1.nextval,sysdate,'RIGHT')");
        q.exec();
    }
    else if (data=="LLL"){
        ui->labelee->setText("LEFT");
        QSqlQuery q;
        q.prepare("INSERT INTO CAR (ID_ACTION,DATE_ACTION,ACTION) VALUES (CAR_SEQ1.nextval,sysdate,'LEFT')");
        q.exec();
    }
    else if (data=="BBB"){
        ui->labelee->setText("BACK");
        QSqlQuery q;
        q.prepare("INSERT INTO CAR (ID_ACTION,DATE_ACTION,ACTION) VALUES (CAR_SEQ1.nextval,sysdate,'BACK')");
        q.exec();
}
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select *from CAR");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDIANTIFIANT_CAR"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("DATE"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ACTION"));
    ui->tablehistorique->setModel(model);
}


void maissa::on_pushButton_8_pressed()
{
   ar.write_to_arduino("F");
}

void maissa::on_pushButton_8_released()
{
    ar.write_to_arduino("K");
}

void maissa::on_pushButton_13_pressed()
{
     ar.write_to_arduino("R");
}

void maissa::on_pushButton_13_released()
{
     ar.write_to_arduino("K");
}

void maissa::on_pushButton_12_pressed()
{
     ar.write_to_arduino("L");
}

void maissa::on_pushButton_12_released()
{
     ar.write_to_arduino("K");
}

void maissa::on_pushButton_14_pressed()
{
     ar.write_to_arduino("B");
}

void maissa::on_pushButton_14_released()
{
     ar.write_to_arduino("K");
}

void maissa::on_map_clicked()
{
    QString program = "D:/Téléchargements/build-MapTest-Desktop_Qt_5_9_9_MinGW_32bit-Debug/debug/MapTest.exe";

            QStringList arguments;
            QProcess *chromeProcess = new QProcess(this);
            chromeProcess->start(program);



}

void maissa::on_pushButton_11_clicked()
{
    QString user=ui->id_supp->text();



    bool test = A.supprimer(user);
    if (test)
    {
         ui->tableView_2->setModel(A.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression done"), QMessageBox::Cancel);



    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("OK"),
                                 QObject::tr("Membre non trouvée!!"), QMessageBox::Cancel);
    }
}
