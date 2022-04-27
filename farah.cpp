#include "farah.h"
#include "ui_farah.h"
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
#include <form.h>
using namespace std;
QT_CHARTS_USE_NAMESPACE
farah::farah(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::farah)
{
    ui->setupUi(this);
    ui->age->setValidator(new QIntValidator(0, 9999999, this));
    ui->id->setValidator(new QIntValidator(0, 9999999, this));
    ui->tel->setValidator(new QIntValidator(0, 9999999, this));
    ui->tableView->setModel(nes.afficher());
    ui->tabdepense1->setModel(de->affichage());
    QSqlQueryModel  *model = new QSqlQueryModel();
    model->setQuery("select id_event, nom_event from evenement");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_event"));

    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom_event"));
    int ret=ar.connect_arduino(); // lancer la connexion à arduino
         switch(ret){
         case(0):qDebug()<< "arduino is available and connected to : "<< ar.getarduino_port_name();
             break;
         case(1):qDebug() << "arduino is available but not connected to :" <<ar.getarduino_port_name();
            break;
         case(-1):qDebug() << "arduino is not available";
         }
          QObject::connect(ar.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
ui->tableView_2->setModel(model);
    QSqlQuery q,q1,q2,q3,q4,q5;
        q.exec("Select * from necessiteux");
        int tot=0;
        while (q.next())
            tot++;
       qDebug() << "total =" << tot;
        q1.prepare("Select * from necessiteux where BESOIN = :nom ");
        q1.bindValue(":nom","C_diabete");
        q1.exec();
        int tot_diab=0;
        while (q1.next())
            tot_diab++;
     qDebug() << "pourcentage diab =" << tot_diab;
        qreal pour_diab=(tot_diab*100)/tot;

        q2.prepare("Select * from necessiteux where BESOIN = :nom ");
        q2.bindValue(":nom","A_sanguin");
        q2.exec();
        int tot_san=0;
        while (q2.next())
            tot_san++;

        qreal pour_san=(tot_san*100)/tot;

        q3.prepare("Select * from necessiteux where BESOIN = :nom ");
        q3.bindValue(":nom","B_cancer");
        q3.exec();
        int tot_ca=0;
        while (q3.next())
            tot_ca++;
        qreal pour_ca=(tot_ca*100)/tot;

        q4.prepare("Select * from necessiteux where BESOIN = :nom ");
        q4.bindValue(":nom","E_vestimentaire");
        q4.exec();
        int tot_vest=0;
        while (q4.next())
            tot_vest++;
        qreal pour_vest=(tot_vest*100)/tot;

        q5.prepare("Select * from necessiteux where BESOIN = :nom ");
        q5.bindValue(":nom","D_faim");
        q5.exec();
        int tot_f=0;
        while (q5.next())
            tot_f++;
        qreal pour_faim=(tot_f*100)/tot;

    QPieSeries *series = new QPieSeries();
     series->append("diabete",pour_diab);
     series->append("Sanguin",pour_san);
     series->append("cancer",pour_ca);
     series->append("vestimentaire",pour_vest);
     series->append("faim",pour_faim);
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
     chart->setTitle("Statistiques des besoins");
     chart->legend()->hide();

     QChartView *chartview = new QChartView(chart,ui->widget);
     chartview->resize(500,400);
     chartview->setRenderHint(QPainter::Antialiasing);



}

farah::~farah()
{
    delete ui;
}
void farah::on_pushButton_4_clicked()
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










void farah::on_pushButton_7_clicked()
{

    QString id=ui->lineEdit_supp->text();
    NECESSITEUX e ;
    e.supprimer(id);

    ui->tableView->setModel(nes.afficher());
}


void farah::on_pushButton_2_clicked()
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


void farah::on_pushButton_8_clicked()
{
    QString nom =ui->lineEdit_9->text();


    if (nom!="")
        ui->tableView->setModel(nes.rechercher(nom));
    else
        ui->tableView->setModel(nes.afficher());

}

void farah::on_pushButton_clicked()
{
     QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM NECESSITEUX ORDER BY MBR_FAMILLE ASC ;");
             ui->tableView->setModel(model);
}

void farah::on_excel_clicked()
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

void farah::on_pushButton_5_clicked()
{
    bool test1;

         QString nomd=ui->lineEdit_23->text();
         QString nom=ui->lineEdit_24->text();
         QString email=ui->lineEdit_25->text();
         QString tel=ui->lineEdit_26->text();
         QString date=ui->lineEdit_29->text();
         QString prix=ui->lineEdit_28->text();
         QString facture=ui->img->text();
    Depense d(nomd,nom,email,tel,date,prix,facture);

    if ((d.verif(nom,prix)))
    {
     test1=d.ajout();
    }
     else test1=false;
    if(test1)
     {
        ui->tabdepense1->setModel(de->affichage());
            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("insertion successful.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

     }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("not"),
                        QObject::tr("insertion failed.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
}

void farah::on_pushButton_9_clicked()
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


void farah::on_pushButton_10_clicked()
{
    /*QSqlQueryModel * model=new QSqlQueryModel();

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
*/
    ui->tableView->setModel(nes.affichagenecessiteux());



}

void farah::on_pushButton_12_clicked()
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
void farah::update_label()
{
    data=ar.read_from_arduino();

    if(data=="1")
        ui->etat->setText("Mouvement"); // si les données reçues de arduino via la liaison série sont égales à 1
    // alors afficher ON

    else if (data=="0")

        ui->etat->setText("Pas de mouvement");   // si les données reçues de arduino via la liaison série sont égales à 0
     //alors afficher ON
   else if (data=="FFF"){
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

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from CAR");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDENTIFIANT_CAR"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("ACTION"));
    ui->tablehistorique->setModel(model);
}

void farah::on_forward_clicked()
{
    ar.write_to_arduino("F");
}

void farah::on_forward_released()
{
     ar.write_to_arduino("K");
}

void farah::on_left_clicked()
{
     ar.write_to_arduino("L");
}

void farah::on_left_released()
{
    ar.write_to_arduino("K");
}

void farah::on_back_clicked()
{
    ar.write_to_arduino("B");
}

void farah::on_back_released()
{
    ar.write_to_arduino("K");
}

void farah::on_right_clicked()
{
    ar.write_to_arduino("R");
}


void farah::on_right_released()
{
    ar.write_to_arduino("K");
}
void farah::on_art_clicked()
{
    ar.write_to_arduino("2");

            ar.write_to_arduino("2");
            QSqlQuery q;
            q.prepare("INSERT INTO ALARM (ID,DATEE) VALUES (ALARM_SEQ.nextval,sysdate)");
            q.exec();

    ui->etat->setText("Arreter");
}
