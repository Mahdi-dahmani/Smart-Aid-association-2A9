#include "mahdi.h"
#include "ui_mahdi.h"
#include "sponsor1.h"
#include <QString>
#include<QMessageBox>
#include <QApplication>
#include <QWidget>
#include<QMovie>
#include <QWidgetAction>
#include "form.h"
#include <stdexcept>
#include "excelexporthelper.h"
#include "historique.h"
#include<QMediaPlayer>
#include<QTimer>
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
#include<QKeyEvent>
QT_CHARTS_USE_NAMESPACE
using namespace std;
mahdi::mahdi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mahdi)
{
    ui->setupUi(this);
    timer =new QTimer (this);
   connect (timer, SIGNAL (timeout()), this, SLOT (myfunction()));
   timer->start (1000);
   QSqlQueryModel  *mod = new QSqlQueryModel();
   mod->setQuery("select id_event, nom_event from evenement");
   mod->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_event"));

   mod->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom_event"));

ui->tableView_3->setModel(mod);
    int ret=A.connect_arduino();
    switch(ret){
    case (0):qDebug()<<"connected"<<A.getarduino_port_name();
        break;
    case(1):qDebug()<<"not connected"<<A.getarduino_port_name();
    break;
    case (-1):qDebug()<<"eruure"<<A.getarduino_port_name();
    }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));

    QSqlQueryModel * modeli =new QSqlQueryModel();



 {       modeli->setQuery("SELECT * FROM historique ;");
         ui->tableView_2->setModel(modeli);
     }
    QMovie *movie = new QMovie("C:/Users/Heisenberg/Desktop/Projet");
    QLabel *processLabel = new QLabel(this);
    processLabel->setMovie(movie);
    movie->start();

    QSqlQueryModel * modell=new QSqlQueryModel();
    modell->setQuery("select * from CAR");
    modell->setHeaderData(0,Qt::Horizontal,QObject::tr("IDENTIFIANT_CAR"));
    modell->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE"));
    modell->setHeaderData(2,Qt::Horizontal,QObject::tr("ACTION"));
    ui->tablehistorique->setModel(modell);
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from SPONSOR");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDENTIFIANT_S"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_S"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM_S"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL_S"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NUM_TEL_S"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ADRESSE_S"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("DATE_DEBUT_S"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("MONTANT_S"));
     ui->tableView->setModel(model);

     QSqlQuery q,q1,q2,q3,q4,q5;
             q.prepare("Select * from sponsor");
             q.exec();
             int tot=0;
             while (q.next())
                 tot++;
            qDebug() << "total =" << tot;
             q1.prepare("Select * from sponsor where MONTANT_SPONSOR < 1000 ");
             q1.exec();
             int tot_2001=0;
             while (q1.next())
                 tot_2001++;
             qDebug() << "total 2001=" << tot_2001;
             qreal pour_2001=(tot_2001*100/tot);

             q2.prepare("Select * from sponsor where MONTANT_SPONSOR BETWEEN 1001 AND 4000 ");
             q2.exec();
             int tot_2000=0;

             while (q2.next())
                 tot_2000++;
             qDebug() << "total 2000=" << tot_2000;
             qreal pour_2000=(tot_2000*100)/tot;

             q3.prepare("Select * from sponsor where MONTANT_SPONSOR BETWEEN 4001 AND 7000 ");
             q3.exec();
             int tot_2003=0;

             while (q3.next())
                 tot_2003++;
          qDebug() << "total 2003=" << tot_2003;
             qreal pour_2003=(tot_2003*100)/tot;

             q4.prepare("Select * from sponsor where MONTANT_SPONSOR BETWEEN 7001 AND 10000 ");
             q4.exec();
             int tot_2005=0;

             while (q4.next())
                 tot_2005++;
          qDebug() << "total 2005=" << tot_2005;
             qreal pour_2005=(tot_2005*100)/tot;

             q5.prepare("Select * from sponsor where MONTANT_SPONSOR > 10000 ");
             q5.exec();
             int tot_2006=0;

             while (q5.next())
                 tot_2006++;
          qDebug() << "total 2006=" << tot_2006;
             qreal pour_2006=(tot_2006*100)/tot;




         QPieSeries *series = new QPieSeries();
          series->append("1000",pour_2001);
          series->append("4000",pour_2000);
          series->append("7000",pour_2003);
          series->append("9000",pour_2005);
          series->append("10000",pour_2006);
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
          chart->setTitle("montant pour chaque departement");
          chart->legend()->hide();

          QChartView *chartview = new QChartView(chart,ui->widget);
          chartview->resize(500,400);
          chartview->setRenderHint(QPainter::Antialiasing);


}

mahdi::~mahdi()
{
    delete ui;
}
void mahdi::on_dial_2_valueChanged(int value)
{
    ui->lcdnumber_2->display(value);
}

void mahdi::on_ajouter_clicked()
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
ui->tableView->setModel(spon.afficher());
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


void mahdi::on_Supprimer_clicked()
{
    QString id=ui->identifiant->text();
        Sponsor1 s;

        bool test=s.supprimer(id);
        if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("supprimer"),
                        QObject::tr("supprimer successful.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tableView->setModel( spon.afficher());
            QString operation="supprimer";
            historique h(operation,id,"mahdi");
             h.Ajouter();
             ui->tableView_2->setModel(h.afficher());}
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("ajouter failed. "),
                        QObject::tr(" supprimer filed"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
           }


}

void mahdi::on_afficher_clicked()
{
    QSqlQueryModel * model =new QSqlQueryModel();

       model->setQuery("SELECT * FROM SPONSOR  ORDER BY IDENTIFIANT_SPONSOR ASC ;");
         ui->tableView->setModel(model);

}
void mahdi::on_Modifier_clicked()
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











void mahdi::on_pushButton_2_clicked()
{
    Form *f= new Form();
    f->show();
}

void mahdi::on_export_2_clicked()
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


void mahdi::update_label()
{


    data=A.read_from_arduino();

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


void mahdi::on_kodem_pressed()
{
   A.write_to_arduino("F");

}

void mahdi::on_kodem_released()
{
     A.write_to_arduino("K");
}

void mahdi::on_imine_pressed()
{
    A.write_to_arduino("R");
}

void mahdi::on_imine_released()
{
    A.write_to_arduino("K");
}

void mahdi::on_isar_pressed()
{
 A.write_to_arduino("L");
}

void mahdi::on_isar_released()
{
    A.write_to_arduino("K");
}

void mahdi::on_lteli_pressed()
{
    A.write_to_arduino("B");

}

void mahdi::on_lteli_released()
{
    A.write_to_arduino("K");
}




void mahdi::on_id_c_clicked()
{
    QSqlQueryModel * model =new QSqlQueryModel();


     model->setQuery("SELECT * FROM SPONSOR  ORDER BY IDENTIFIANT_SPONSOR ASC ;");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDENTIFIANT_S"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_S"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM_S"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL_S"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("NUM_TEL_S"));
     model->setHeaderData(5,Qt::Horizontal,QObject::tr("ADRESSE_S"));
     model->setHeaderData(6,Qt::Horizontal,QObject::tr("DATE_DEBUT_S"));
     model->setHeaderData(7,Qt::Horizontal,QObject::tr("MONTANT_S"));
         ui->tableView->setModel(model);

}

void mahdi::on_nom_c_clicked()
{QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM SPONSOR  ORDER BY NOM_SPONSOR ASC ;");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDENTIFIANT_S"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_S"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM_S"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL_S"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NUM_TEL_S"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ADRESSE_S"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("DATE_DEBUT_S"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("MONTANT_S"));
             ui->tableView->setModel(model);
}

void mahdi::on_prenom_c_clicked()
{QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM SPONSOR  ORDER BY PRENOM_SPONSOR DESC ;");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDENTIFIANT_S"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_S"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM_S"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL_S"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NUM_TEL_S"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ADRESSE_S"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("DATE_DEBUT_S"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("MONTANT_S"));
             ui->tableView->setModel(model);
}

void mahdi::on_email_c_clicked()
{QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM SPONSOR  ORDER BY EMAIL_SPONSOR ASC ;");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDENTIFIANT_S"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_S"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM_S"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL_S"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NUM_TEL_S"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ADRESSE_S"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("DATE_DEBUT_S"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("MONTANT_S"));
             ui->tableView->setModel(model);

}

void mahdi::on_num_c_clicked()
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM SPONSOR  ORDER BY NUM_TEL_SPONSOR ASC ;");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDENTIFIANT_S"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_S"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM_S"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL_S"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NUM_TEL_S"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ADRESSE_S"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("DATE_DEBUT_S"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("MONTANT_S"));
             ui->tableView->setModel(model);
}

void mahdi::on_adresse_c_clicked()
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM SPONSOR  ORDER BY ADRESSE_SPONSOR ASC ;");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDENTIFIANT_S"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_S"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM_S"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL_S"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NUM_TEL_S"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ADRESSE_S"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("DATE_DEBUT_S"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("MONTANT_S"));
             ui->tableView->setModel(model);
}

void mahdi::on_Dtate_c_clicked()
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM SPONSOR  ORDER BY DATE_DEBUT_SPONSOR ASC ;");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDENTIFIANT_S"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_S"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM_S"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL_S"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NUM_TEL_S"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ADRESSE_S"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("DATE_DEBUT_S"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("MONTANT_S"));
             ui->tableView->setModel(model);

}

void mahdi::on_montant_c_clicked()
{
 QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM SPONSOR  ORDER BY MONTANT_SPONSOR ASC ;");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDENTIFIANT_S"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_S"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM_S"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL_S"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NUM_TEL_S"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ADRESSE_S"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("DATE_DEBUT_S"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("MONTANT_S"));
    ui->tableView->setModel(model);
}




void mahdi::on_sponsor_2_clicked()
{
    mahdi p1;
    QString idA = ui->sponsor->text();
    int qnt;
    bool test;
    QSqlQuery qry;
    qry.prepare("select MONTANT_SPONSOR from SPONSOR where IDENTIFIANT_SPONSOR = "+idA+" ");
    if (qry.exec()){
        while (qry.next()){
            qnt = (qry.value(0).toInt());
            if (qnt >= 5000){
                test = true;
            }else{
                test = false;
            }
        }
    }
        QMessageBox msgbox;
        if (test){
                ui->tableView->setModel(spon.afficher());
                QMessageBox::information(nullptr, QObject::tr("etait sponsor"),
                                      QObject::tr("Ce Sponsor est important"),
                                      QMessageBox::Ok
                                      );
            }else{
                QMessageBox::critical(nullptr, QObject::tr("etait sponsor"),
                                      QObject::tr("Ce Sponsor est moyen"),
                                      QMessageBox::Cancel
                                      );
            }
    }


void mahdi::on_identifiant_editingFinished()
{

    QString val=ui->identifiant->text();
    QString option=ui->option->currentText();
     if((val!="")&&(option=="Id"))
 {        ui->tableView->setModel(spon.afficher_recherche0(val));

     }
     else if((val!="")&&(option=="Nom"))
     {
        ui->tableView_2->setModel(spon.afficher_recherche2(val));
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
        ui->tableView->setModel(spon.afficher_recherche0(val));

     }
}

void mahdi::on_pushButton_3_clicked()
{
    QTime time = QTime::currentTime();
   QString time_text= time.toString ("hh :mm: ss");
   ui->temps->setText(time_text);
}





void mahdi::on_gif_linkActivated(const QString &link)
{
    QMovie *movie = new QMovie("C:/Users/user/Desktop/2eme/Semestre 2/Projet QT/sponsor/Projet/mahdi.gif");
    QLabel *processLabel = new QLabel(this);
    processLabel->setMovie(movie);
    movie->start();
}



void mahdi::on_temps_linkActivated(const QString &link)
{
    QTime time = QTime::currentTime();
   QString time_text= time.toString ("hh :mm: ss");
   ui->temps->setText(time_text);
}
void mahdi::myfunction()
{


   QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz");
   ui->temps_2->setText(sDate);
}

void mahdi::on_pushButton_7_clicked()
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
void mahdi::on_forward_clicked()
{
    A.write_to_arduino("F");
}

void mahdi::on_forward_released()
{
     A.write_to_arduino("K");
}

void mahdi::on_left_clicked()
{
     A.write_to_arduino("L");
}

void mahdi::on_left_released()
{
    A.write_to_arduino("K");
}

void mahdi::on_back_clicked()
{
    A.write_to_arduino("B");
}

void mahdi::on_back_released()
{
    A.write_to_arduino("K");
}

void mahdi::on_right_clicked()
{
    A.write_to_arduino("R");
}


void mahdi::on_right_released()
{
    A.write_to_arduino("K");
}
void mahdi::on_art_clicked()
{
    A.write_to_arduino("0");
    ui->etat->setText("Arréter");
    QSqlQuery q;
    q.prepare("INSERT INTO ALARM (ID,DATEE) VALUES (ALARM_SEQ.nextval,sysdate)");
    q.exec();
}
