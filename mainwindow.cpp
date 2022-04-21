#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "donateurs.h"
#include <QMessageBox>
#include <QTableView>
#include <string>
#include <string.h>
#include <ActiveQt/qaxobject.h>
#include <ActiveQt/qaxbase.h>
#include <QFile>
#include <stdexcept>
#include "excelexporthelper.h"
#include "form.h"
#include "dons.h"
#include "arduino.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(dtmp.afficher());
     ui->tableView_2->setModel(dotmp.afficherd());


     int ret=A.connect_arduino(); // lancer la connexion à arduino
     switch(ret){
     case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
         break;
     case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
        break;
     case(-1):qDebug() << "arduino is not available";
     }
      QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
      //le slot update_label suite à la reception du signal readyRead (reception des données).


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    bool test;
    QString ID_DONATEUR=ui->lineEdit_17->text();
    QString NOM_DONATEUR=ui->lineEdit->text();
    QString TEL_DONATEUR=ui->lineEdit_2->text();
    QString ADRESSE_DONATEUR=ui->lineEdit_3->text();
     QString DON_DONATEUR=ui->lineEdit_4->text();
    donateurs d(ID_DONATEUR,NOM_DONATEUR,TEL_DONATEUR,ADRESSE_DONATEUR,DON_DONATEUR);
    if ((d.check(NOM_DONATEUR))&&(d.check_tlf(TEL_DONATEUR)))
    test=d.ajouter();
    else {QMessageBox::information(nullptr ,QObject::tr("ok"),
                                   QObject::tr("NOM   ou Telephone FORMART INCORRECT\n"
                                "click cancel to exit")
                                     , QMessageBox::Cancel
                                     );
    test=false;}
    if (test)
    {
         QMessageBox::information(nullptr ,QObject::tr("ok"),
                                QObject::tr("ajout done \n"
                             "click cancel to exit")
                                  , QMessageBox::Cancel
                                  );
         ui->tableView->setModel(dtmp.afficher());
    }
   else  QMessageBox::critical(nullptr,QObject::tr("not ok"),
                               QObject::tr("ajout non eff \n"
                                 "click cancel to exit")
                               , QMessageBox::Cancel
                               );
}

void MainWindow::on_pushButton_12_clicked()
{
    QString ID_DONATEUR =ui->lineEdit_18->text();
    bool test=dtmp.supprimer(ID_DONATEUR);
    if (test)
    {
         QMessageBox::information(nullptr ,QObject::tr("ok"),
                                QObject::tr("suppr done \n"
                             "click cancel to exit")
                                  , QMessageBox::Cancel
                                  );
ui->tableView->setModel(dtmp.afficher());
    }
   else  QMessageBox::critical(nullptr,QObject::tr("not ok"),
                               QObject::tr("suppr non eff \n"
                                 "click cancel to exit")
                               , QMessageBox::Cancel
                               );
}

void MainWindow::on_pushButton_13_clicked()
{
    QString nom=ui->lineEdit_rech->text();


        if (nom!="")
        ui->tableView->setModel(dtmp.rechercher(nom));
        else
             ui->tableView->setModel(dtmp.afficher());

}

void MainWindow::on_pushButton_3_clicked()
{
    QString ID_DONATEUR =ui->lineEdit_16->text();
    QString NOM_DONATEUR=ui->lineEdit_nom->text();
    QString TEL_DONATEUR=ui->lineEdit_tlp->text();
    QString ADRESSE_DONATEUR=ui->lineEdit_add->text();
     QString DON_DONATEUR=ui->lineEdit_typedon->text();
donateurs d(NOM_DONATEUR,TEL_DONATEUR,ADRESSE_DONATEUR,DON_DONATEUR);
    bool test=d.modifier(ID_DONATEUR);
    if (test)
    {
        ui->tableView->setModel(dtmp.afficher());
         QMessageBox::information(nullptr ,QObject::tr("ok"),
                                QObject::tr("modif done \n"
                             "click cancel to exit")
                                  , QMessageBox::Cancel
                                  );
ui->tableView->setModel(dtmp.afficher());
    }
   else  QMessageBox::critical(nullptr,QObject::tr("not ok"),
                               QObject::tr("modiif non eff \n"
                                 "click cancel to exit")
                               , QMessageBox::Cancel
                               );

}

void MainWindow::on_trie_clicked()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT* FROM donateurs  ORDER BY to_number(id_donateur) ASC ;");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_DONATEUR"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_donateur"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Tel_donateur"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Adresse_donateur"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Don_donateur"));
             ui->tableView->setModel(model);
}

void MainWindow::on_lineEdit_editingFinished()
{

}

void MainWindow::on_excel_clicked()
{
    try
           {
               const QString fileName = "c:\\test.xlsx";

               ExcelExportHelper helper;
   int l=2;
               QSqlQuery q;
               if(q.exec("SELECT * FROM donateurs"))
               {
   helper.SetCellValue(1,1,"id_donateur");
   helper.SetCellValue(1,2,"NOM_DONATEUR");
   helper.SetCellValue(1,3,"TEL_DONATEUR");
   helper.SetCellValue(1,4,"ADRESSE_DONATEUR");
   helper.SetCellValue(1,5,"DON_DONATEUR");

                   while (q.next())
                   {

               helper.SetCellValue(l,1,q.value(0).toString());
               helper.SetCellValue(l,2,q.value(1).toString());
               helper.SetCellValue(l,3,q.value(2).toString());
               helper.SetCellValue(l,4,q.value(3).toString());
               helper.SetCellValue(l,5,q.value(4).toString());

   l++;

                   }
               helper.SaveAs(fileName);
           }}
           catch (const exception& e)
           {
               QMessageBox::critical(this, "Error - Demo", e.what());
           }
}

void MainWindow::on_pushButton_7_clicked()
{
    Form *f=new Form();
    f->show();
}



void MainWindow::on_boutonajoutdon_clicked()
{
    bool test;
    QString id_don=ui->id_don->text();
    QString id_donateur=ui->iddonateurr->text();
    QString type_don=ui->comboBox1->currentText();
    QString quantitee=ui->quantiteedon->text();
QString cathegorie;
    if (type_don=="vetement"){
  cathegorie= (ui->c1->currentText()) += (ui->c2->currentText());}
    else if (type_don=="meuble")
    { cathegorie=ui->c3->currentText(); }
    else { cathegorie=ui->c4->text() ;}

    Dons d(id_don,id_donateur ,quantitee,type_don,cathegorie);

    test=d.ajouterd();

    if (test)
    {
         QMessageBox::information(nullptr ,QObject::tr("ok"),
                                QObject::tr("ajout done \n"
                             "click cancel to exit")
                                  , QMessageBox::Cancel
                                  );
         ui->tableView_2->setModel(dotmp.afficherd());
    }
   else  QMessageBox::critical(nullptr,QObject::tr("not ok"),
                               QObject::tr("ajout non effectue \n"
                                 "click cancel to exit")
                               , QMessageBox::Cancel
                               );
}

void MainWindow::on_supprimerdon_clicked()
{


    QString id_don=ui->lineEdit_22->text();
    bool test=dotmp.supprimerd(id_don);
    if (test)
    {
         QMessageBox::information(nullptr ,QObject::tr("ok"),
                                QObject::tr("suppr done \n"
                             "click cancel to exit")
                                  , QMessageBox::Cancel
                                  );
ui->tableView_2->setModel(dotmp.afficherd());
    }
   else  QMessageBox::critical(nullptr,QObject::tr("not ok"),
                               QObject::tr("suppr non eff \n"
                                 "click cancel to exit")
                               , QMessageBox::Cancel
                               );
}

void MainWindow::on_pushButton_4_clicked()
{ QString id_don=ui->lineEdit_21->text();
    QString id_donateur=ui->lineEdit_20->text();
    QString type_don=ui->comboBox_3->currentText();
    QString quantitee=ui->lineEdit_tlp_2->text();
    QString cathegorie;

      if (type_don=="vetement"){
      cathegorie= (ui->c11->currentText()) += (ui->c22->currentText());}
        else if (type_don=="meuble")
        { cathegorie=ui->c33->currentText() ;}
        else { cathegorie=ui->c44->text() ;}


Dons d1(id_don,id_donateur ,quantitee,type_don,cathegorie);
    bool test=d1.modifierd(id_don);
    if (test)
    {
        ui->tableView_2->setModel(dotmp.afficherd());
         QMessageBox::information(nullptr ,QObject::tr("ok"),
                                QObject::tr("modif done \n"
                             "click cancel to exit")
                                  , QMessageBox::Cancel
                                  );
ui->tableView_2->setModel(dotmp.afficherd());
    }
   else  QMessageBox::critical(nullptr,QObject::tr("not ok"),
                               QObject::tr("modiif non eff \n"
                                 "click cancel to exit")
                               , QMessageBox::Cancel
                               );
}


void MainWindow::update_label()
{
    data=A.read_from_arduino();

    if(data=="1")

        ui->etat->setText("Mouvement"); // si les données reçues de arduino via la liaison série sont égales à 1
    // alors afficher ON

    else if (data=="0")

        ui->etat->setText("Pas de mouvement");   // si les données reçues de arduino via la liaison série sont égales à 0
     //alors afficher ON
}

/*void MainWindow::on_pushButton_clicked()   // implémentation du slot bouton on
{
     A.write_to_arduino("1"); //envoyer 1 à arduino
}
*/
void MainWindow::on_pushButton_2_clicked()  // implémentation du slot bouton off
{

      //envoyer 0 à arduino
}
/*
void MainWindow::on_pushButton_3_clicked()  // implémentation du slot bouton +
{
    A.write_to_arduino("2");   //envoyer 2 à arduino
}

void MainWindow::on_pushButton_4_clicked() // implémentation du slot bouton -
{
    A.write_to_arduino("3");  //envoyer 3 à arduino
}*/

void MainWindow::on_art_clicked()
{
    A.write_to_arduino("0");
    ui->etat->setText("Arréter");
}
