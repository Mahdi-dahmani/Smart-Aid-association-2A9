#include "mainwindow.h"
#include <QMessageBox>
#include <QApplication>
#include "connection.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool check = c.createconnect();
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
