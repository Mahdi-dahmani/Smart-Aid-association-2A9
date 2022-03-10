#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "necessiteux.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QIntValidator>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->age->setValidator(new QIntValidator(0, 9999999, this));
    ui->id->setValidator(new QIntValidator(0, 9999999, this));
    ui->tableView->setModel(nes.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_4_clicked()
{
    QString id=ui->id->text();
    QString nom=ui->nom->text();
    QString sexe=ui->sexe->text();
    QString age=ui->age->text();
    QString tel=ui->tel->text();
    QString adresse=ui->adresse->text();
    QString mbr=ui->mbr->text();
    QString besoin=ui->besoin->text();
    QString date=ui->date->text();

    NECESSITEUX e(id,nom,sexe,age,tel,adresse,mbr,besoin,date);
    if (nom.isEmpty()||adresse.isEmpty()||id==0)
    {
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                 QObject::tr("Case Obligatoire!\n"),QMessageBox::Cancel );
    }
    else
        if(!(nom.contains(QRegExp("^[A-Za-z]+$"))))
                {

                    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                             QObject::tr("Veuillez entrer une chaine!\n"
                                                         "Click Cancel to exit. "),QMessageBox::Cancel);

                }
    else
        {
            e.ajouter();
            ui->tableView->setModel(nes.afficher());

        }

}










void MainWindow::on_pushButton_7_clicked()
{

    QString id=ui->lineEdit_supp->text();
    NECESSITEUX e ;
    e.supprimer(id);

    ui->tableView->setModel(nes.afficher());
}


void MainWindow::on_pushButton_2_clicked()
{
    QString id=ui->lineEdit->text();
    QString nom=ui->lineEdit_2->text();
    QString sexe=ui->lineEdit_3->text();
    QString age=ui->lineEdit_4->text();
    QString tel=ui->lineEdit_5->text();
    QString adresse=ui->lineEdit_6->text();
    QString besoin=ui->lineEdit_7->text();
    QString mbr=ui->spinBox->text();

    QString date=ui->dateEdit->text();
    NECESSITEUX e(id,nom,sexe,age,tel,adresse,mbr,besoin,date);
    if (nom.isEmpty()||adresse.isEmpty()||id==0)
    {
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                 QObject::tr("Case Obligatoire!\n"),QMessageBox::Cancel );
    }
    else
        if(!(nom.contains(QRegExp("^[A-Za-z]+$"))))
                {

                    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                             QObject::tr("Veuillez entrer une chaine!\n"
                                                         "Click Cancel to exit. "),QMessageBox::Cancel);

                }
        else{
            bool test = e.modifier(id);
            if (test)
            {
               ui->tableView->setModel(nes.afficher());
               QMessageBox::information(nullptr,QObject::tr("OK"),
                                        QObject::tr("Edit done"),QMessageBox::Cancel );
            }
            else
            {
                QMessageBox::critical(nullptr , QObject::tr("OK"),
                                      QObject::tr("Edit impossible") , QMessageBox::Cancel );
            }
        }

        }


void MainWindow::on_pushButton_8_clicked()
{
    QString nom =ui->lineEdit_9->text();


    if (nom!="")
        ui->tableView->setModel(nes.rechercher(nom));
    else
        ui->tableView->setModel(nes.afficher());

}

void MainWindow::on_pushButton_clicked()
{
     QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM NECESSITEUX ORDER BY MBR_FAMILLE ASC ;");
             ui->tableView->setModel(model);
}
