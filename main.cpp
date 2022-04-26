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
#include "maraaa.h"
#include <QMessageBox>
#include <QApplication>
#include "connection.h"
#include "form.h"
#include "ui_form.h"
#include <QtWidgets/QApplication>
#include <QFile>
#include <QMediaPlayer>
QT_CHARTS_USE_NAMESPACE
int main(int argc, char *argv[])
{ //hola
    //hii
    //how are u

   QApplication a(argc, argv);
     QFile styleSheetFile("C:/Users/user/Desktop/2eme/Semestre 2/Projet QT/Projet/Irrorater.qss");
    qDebug() << QFile::exists("C:/Users/user/Desktop/2eme/Semestre 2/Projet QT/Projet/Irrorater.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet);
    Connection c;
   c.createconnect();
   QMediaPlayer * music =new QMediaPlayer;
   music->setMedia(QUrl::fromLocalFile(""));
  music->play();
Login l;
l.show();
    return a.exec();
}
