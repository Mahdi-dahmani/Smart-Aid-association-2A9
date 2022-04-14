#include "form.h"
#include "ui_Form.h"
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



    ui->setupUi(this);
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

Form::~Form()
{
    delete ui;
}
