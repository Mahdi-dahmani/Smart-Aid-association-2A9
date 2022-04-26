#include "iheb.h"
#include "ui_iheb.h"
#include "depense.h"
#include "connection.h"
#include <QMessageBox>
#include <QApplication>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QBuffer>
#include <QTextTable>
#include <QScreen>
#include <QSqlQueryModel>
#include <QPainter>
#include <QtPrintSupport/QPrinter>
#include <QTextTable>
#include <QTextTableCell>
#include <QTextTableFormat>
#include <excelexporthelper.h>
#include <exception>
#include <QtCharts/QChartView>
#include <QDebug>
#include <arduino.h>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>

#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

QT_CHARTS_USE_NAMESPACE

iheb::iheb(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::iheb)
{
    ui->setupUi(this);
    ui->tabdepense1->setModel(de->affichage());
    QSqlQueryModel  *model = new QSqlQueryModel();
    model->setQuery("select id_membre, nom_membre, prenom_membre from Membres");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_Membre"));

    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom_Membre"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom_Membre"));
ui->tableView_2->setModel(model);
}

iheb::~iheb()
{
    delete ui;
}
void iheb ::on_pushButton_4_clicked()
{
bool test1;

     QString nomd=ui->lineEdit_23->text();
     QString nom=ui->lineEdit_24->text();
     QString email=ui->lineEdit_25->text();
     QString tel=ui->lineEdit_26->text();
     QString date=ui->lineEdit_29->text();
     QString prix=ui->lineEdit_28->text();
     QString facture=ui->piclabel1->text();
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








void iheb::on_suprim_clicked()
{
    QString sup=ui->supp->text();
    bool test=de->suprimer(sup);
    if(test)
     {
        ui->tabdepense1->setModel(de->affichage());
            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr(" successful delete.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

     }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("not"),
                        QObject::tr(" failed delete.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
}

void iheb::on_pushButton_6_clicked()
{
QString ids=ui->lineEdit_ids->text();
    QString nom=ui->lineEdit_nom->text();
    QString nomd=ui->lineEdit_nomd->text();
    QString email=ui->lineEdit_email->text();
    QString tel=ui->lineEdit_tel->text();
    QString date=ui->lineEdit_7->text();
    QString prix=ui->lineEdit_prix->text();
QString etat=ui->lineEdit_etat->text();
    bool test = de->modifier(ids,nom,nomd,email,tel,date,prix,etat);
    if (test)
    {
        ui->tabdepense1->setModel(de->affichage());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Edit done"), QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("OK"),
                                 QObject::tr("Edit failed"), QMessageBox::Cancel);
    }
}

void iheb::on_search_clicked()
{
    QString ids=ui->lineEdit_ids->text();
    QSqlQuery query;

    query.prepare("select nom_depense,nom_depensier,email_depensier,tel_depensier,date_depense,prix_depense,etat_depense from depense Where id_depense=:id");

     query.bindValue(":id",ids);
     query.exec();
     query.next();
      QString nom=query.value("nom_depense").toString();
     // qDebug()<<nom;

     ui->lineEdit_nom->setText(nom);
     ui->lineEdit_nomd->setText(query.value("nom_depensier").toString());
       ui->lineEdit_email->setText(query.value("email_depensier").toString());
        ui->lineEdit_tel->setText(query.value("tel_depensier").toString());
         ui->lineEdit_7->setText(query.value("date_depense").toString());
          ui->lineEdit_prix->setText(query.value("prix_depense").toString());
          ui->lineEdit_etat->setText(query.value("etat_depense").toString());

 }
/*void MainWindow::slotCurrentPic()
{


    QModelIndex index;
        QSqlQueryModel model;
        QByteArray bytes;

        QSqlQuery query;

            model.setQuery("SELECT facture_depense FROM depense WHERE id_depense=3");
            index = model.index(0,0);
            bytes = index.data().toByteArray();
            QPixmap outPixmap = QPixmap(); // Create QPixmap, which will be placed in picLabel
            // Taking the image data from the table as QByteArray and put them in QPixmap


            outPixmap.loadFromData(bytes);
            ui->picLabel->setPixmap(outPixmap.scaled(400,200, Qt::KeepAspectRatio));

}




void MainWindow::on_pushButton_2_clicked()
{
 QSqlQuery q;
  //  slotCurrentPic();
    QString fileName = QFileDialog::getOpenFileName(this,tr("choose an image"), "",tr("All Files (*)"));

        qDebug()<<fileName+"url" ;
        QFile file(fileName);
             if (!file.open(QIODevice::ReadOnly)) return;
             QByteArray inByteArray = file.readAll();
      //  QPixmap outPixmap=QPixmap();
        // outPixmap.loadFromData(inByteArray);
      //  ui->picLabel->setPixmap(outPixmap.scaled(400,200, Qt::KeepAspectRatio));
        q.prepare("update depense  set facture_depense= :img where id_depense = :id");
        q.bindValue(":id","3");
        q.bindValue(":img",inByteArray);
        q.exec();


}*/

void iheb::on_img_clicked()
{
    QSqlQuery q;
     //  slotCurrentPic();
       QString fileName = QFileDialog::getOpenFileName(this,tr("choose an image"), "",tr("All Files (*)"));

           qDebug()<<fileName+"url" ;

           ui->piclabel1->setText(fileName);
}






void iheb::on_pushButton_5_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("choose an image"), "",tr("All Files (*)"));
qDebug() <<fileName;
    de->billan(fileName);
}


/*void MainWindow::on_tabdepense1_activated(const QModelIndex &index)
{
    qDebug() <<"in";
    QString val=ui->tabdepense1->model()->data(index).toString();
    QString sql = QString("select * from depense");
            QSqlQuery query2;
            query2.prepare("select * from depense where id_depense=:id");
            query2.bindValue(":id","3");
            query2.exec();
            if (query2.isActive()) {


                 while(query2.next()){
                 QByteArray inByteArray=query2.value("facture_depense").toByteArray();
                 QPixmap outPixmap=QPixmap();
                outPixmap.loadFromData(inByteArray);

ui->label_10->setPixmap(outPixmap.scaled(10,20, Qt::KeepAspectRatio));
                 }
            }
}*/

void iheb::on_tabdepense1_clicked(const QModelIndex &index)
{
    qDebug() <<"in";
    QString val=ui->tabdepense1->model()->data(index).toString();
    val.remove("facture N");
    QString sql = QString("select * from depense");
            QSqlQuery query2;
            query2.prepare("select * from depense where id_depense=:id");
            query2.bindValue(":id",val);
            query2.exec();
            if (query2.isActive()) {

               query2.seek(0);

                 QByteArray inByteArray=query2.value("facture_depense").toByteArray();
                 QPixmap outPixmap=QPixmap();
                outPixmap.loadFromData(inByteArray);

//ui->label_10->setPixmap(outPixmap.scaled(100,200, Qt::KeepAspectRatio));
QLabel * label_img = new QLabel ();
label_img->setWindowFlags(Qt::Window);
label_img->setPixmap(outPixmap.scaled(400,500, Qt::KeepAspectRatio));
label_img->show();
            }
}


void iheb::on_pushButton_7_clicked()
{
   /* try
            {*/
                const QString fileName = "c:\\test.xlsx";

                ExcelExportHelper helper;
    int l=2;
                QSqlQuery q;
                if(q.exec("SELECT id_depense,nom_depense,date_depense,prix_depense,nom_depensier,email_depensier,tel_depensier,etat_depense FROM depense"))
                {
    helper.SetCellValue(1,1,"ID");
    helper.SetCellValue(1,2,"NOM");
    helper.SetCellValue(1,3,"date");
    helper.SetCellValue(1,4,"prix");
    helper.SetCellValue(1,5,"nom depensier");
    helper.SetCellValue(1,6,"email");
    helper.SetCellValue(1,7,"tel");
    helper.SetCellValue(1,8,"etat ");
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
            /*catch (const exception &e)
            {
                QMessageBox::critical(this, "Error - Demo", e.what());
            }
}*/

void iheb::on_statsbuttton_clicked()
{
    int rowc=0;
    int total=0;
    int pr=0;

     QPieSeries *series = new QPieSeries();
    QString sql = QString("select nom_depense,prix_depense from depense");
            QSqlQuery query2(sql);
            if (query2.isActive()) {
                qDebug() <<"good";
                while (query2.next()) {
                    rowc++;
                }
                for(int i=0;i < rowc;i++)
                {
                 query2.seek(i);
                 total+=query2.value("prix_depense").toInt();

                 }
           // 4. Pie Chart Example
           // Define slices and percentage of whole they take up

           for(int i=0;i < rowc;i++)
           {
            query2.seek(i);
            pr=((query2.value("prix_depense").toInt())*100)/total;
            double prc=("." + QString::number(pr)).toDouble();
            series->append(query2.value("nom_depense").toString(),prc);
            qDebug() <<prc;


            qDebug() <<"good";

           // Add label to 1st slice
           QPieSlice *slice0 = series->slices().at(i);
           slice0->setLabelVisible();
           slice0->setExploded();
           //slice0->setPen(QPen(Qt::darkGreen, 2));
           // Add label, explode and define brush for 2nd slice
           /*QPieSlice *slice1 = series->slices().at(1);
           slice1->setExploded();
           slice1->setLabelVisible();
           slice1->setPen(QPen(Qt::darkGreen, 2));
           slice1->setBrush(Qt::green);

           // Add labels to rest of slices
           QPieSlice *slice2 = series->slices().at(2);
           slice2->setLabelVisible();
           QPieSlice *slice3 = series->slices().at(3);
           slice3->setLabelVisible();
           /*QPieSlice *slice4 = series->slices().at(4);
           slice4->setLabelVisible();*/
           }
    }
           // Create the chart widget
           QChart *chart = new QChart();

           // Add data to chart with title and hide legend
           chart->addSeries(series);
           chart->setTitle("le pourcentage de chaque depense");
           chart->legend()->hide();

           // Used to display the chart
           QChartView *chartView = new QChartView(chart);
           chartView->setRenderHint(QPainter::Antialiasing);
chartView->setWindowFlags(Qt::Window);
chartView->resize(420, 300);
chartView->show();
           // Create the main app window
           /*QMainWindow window;

           // Set the main window widget
           QLabel * label_img = new QLabel ();
           label_img->setWindowFlags(Qt::Window);
           label_img->setProperty()
           label_img->show();
           window.setCentralWidget(chartView);
           window.resize(420, 300);
           window.show();*/
}

void iheb::on_pushButton_8_clicked()
{
    if(!(ui->lineEdit_search->text().isEmpty()))
    {
    QString search=ui->lineEdit_search->text();
    ui->tabdepense1->setModel(de->recherche(search));
    }
    else
        ui->tabdepense1->setModel(de->affichage());
}

void iheb::on_pushButton_web_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("choose an image"), "",tr("All Files (*)"));
qDebug() <<fileName;
    de->billanweb(fileName);
}



void iheb::on_pushButton_2_clicked()
{
    ui->tabdepense1->setModel(de->affichagetri());
    //SELECT * FROM Customers
    //ORDER BY CustomerName ASC;
}



void iheb::on_arduino_clicked()
{
    ui->tabdepense1->setModel(de->affichage());


A.write_to_arduino("2");

        A.write_to_arduino("2");
        QSqlQuery q;
        q.prepare("INSERT INTO ALARM (ID,DATEE) VALUES (ALARM_SEQ.nextval,sysdate)");
        q.exec();

ui->etat->setText("Arreter");

}
void iheb::update_label()
{
    data=A.read_from_arduino();

    if(data=="1")
        ui->etat->setText("Mouvement"); // si les données reçues de arduino via la liaison série sont égales à 1
    // alors afficher ON

    else if (data=="0")

        ui->etat->setText("Pas de mouvement");   // si les données reçues de arduino via la liaison série sont égales à 0
     //alors afficher ON
}

void iheb::on_pushButton_11_clicked()
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
