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
#include "dons.h"
QT_CHARTS_USE_NAMESPACE
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{

    QSqlQuery q,q1,q2,q3,q4,q5;
        q.exec("Select * from Dons");
        int tot=0;
        while (q.next())
            tot++;
       qDebug() << "total =" << tot;
        q1.prepare("Select * from Dons where  SUBSTR(cathegorie, 1, 5)= :homme ");
        q1.bindValue(":homme","homme");
        q1.exec();
        int tot_homme=0;
        while (q1.next())
            tot_homme++;
     qDebug() << "pourcentage don =" << tot_homme;
        qreal pour_homme=(tot_homme*100)/tot;

        q2.prepare("Select * from dons where SUBSTR(cathegorie, 1, 5)= :femme ");
        q2.bindValue(":femme","femme");
        q2.exec();
        int tot_femme=0;
        while (q2.next())
            tot_femme++;

        qreal pour_femme=(tot_femme*100)/tot;

        q3.prepare("Select * from dons where SUBSTR(cathegorie, 1, 5)= :garco ");
        q3.bindValue(":garco","garco");
        q3.exec();
        int tot_garco=0;
        while (q3.next())
            tot_garco++;
        qreal pour_garco=(tot_garco*100)/tot;

        q4.prepare("Select * from Dons where SUBSTR(cathegorie, 1, 5)= :fille ");
        q4.bindValue(":fille","fille");
        q4.exec();
        int tot_fille=0;
        while (q4.next())
            tot_fille++;
        qreal pour_fille=(tot_fille*100)/tot;
        q5.prepare("Select * from Dons where SUBSTR(cathegorie, 1, 5)= :bebee ");
        q5.bindValue(":bebee","bebee");
        q5.exec();
        int tot_bebee=0;
        while (q5.next())
            tot_bebee++;
        qreal pour_bebee=(tot_bebee*100)/tot;





    ui->setupUi(this);
    QPieSeries *series = new QPieSeries();
     series->append("homme",pour_homme);
     series->append("femme",pour_femme);
     series->append("fille",pour_fille);
     series->append("garco",pour_garco);
     series->append("bebee",pour_bebee);

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
     chart->setTitle("sexe et age");
     chart->legend()->hide();

     QChartView *chartview = new QChartView(chart,ui->widget);
     chartview->resize(500,400);
     chartview->setRenderHint(QPainter::Antialiasing);




}

Form::~Form()
{
    delete ui;
}
