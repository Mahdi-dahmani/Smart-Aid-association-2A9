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
    ui->setupUi(this);
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

Form::~Form()
{
    delete ui;
}
