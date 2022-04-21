#include "form.h"
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
#include"ui_form.h"
QT_CHARTS_USE_NAMESPACE
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{

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





    ui->setupUi(this);
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

Form::~Form()
{
    delete ui;
}
