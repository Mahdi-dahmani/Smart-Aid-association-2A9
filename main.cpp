#include "mainwindow.h"
#include "evenement.h"
#include "connection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test = c.createconnect();
    MainWindow w;
    w.show();
    return a.exec();
}
