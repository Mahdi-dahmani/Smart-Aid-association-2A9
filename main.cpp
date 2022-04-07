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
#include "mainwindow.h"
#include "login.h"

#include <QMessageBox>
#include <QApplication>
#include "connection.h"
#include "form.h"
#include "ui_form.h"
QT_CHARTS_USE_NAMESPACE
int main(int argc, char *argv[])
{ //hola
    //hii
    //how are u

    QApplication a(argc, argv);

    Connection c;
    bool check = c.createconnect();
    Login l;
    l.show();
MainWindow w;
    w.show();



    if (check)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("done"), QMessageBox::Cancel);



    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("OK"),
                                 QObject::tr("Non"), QMessageBox::Cancel);
    }


    return a.exec();
}
