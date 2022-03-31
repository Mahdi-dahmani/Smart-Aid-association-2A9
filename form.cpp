#include "form.h"
#include "ui_form.h"
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
QT_CHARTS_USE_NAMESPACE
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
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
    ui->setupUi(this);
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


    /* MainWindow w;
     w.setCentralWidget(chartview);
     w.resize(420,300);
 w.show();*/

}

Form::~Form()
{
    delete ui;
}

