#include "depense.h"
#include "connection.h"
#include <QSqlQuery>
#include <QString>
#include <QObject>
#include <QSqlQueryModel>
#include <QDebug>
#include <string.h>
#include <string>
#include <QFile>
#include <QDate>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QPainter>
#include <QPrinter>
#include <QTextDocument>
#include <QPrintDialog>
#include <QTextBrowser>
#include <QApplication>
#include <QTextBrowser>
#include <QStandardItem>
using namespace std;
Depense::Depense()
{

}
Depense::Depense(QString b,QString c,QString d,QString e,QString f,QString g,QString i)
{

    nom_depense=b;
    nom_depensier=c;
    email_depensier=d;
    tel_depensier=e;
    date_depense=f;
    prix_depense=g;
    facture_depense=i;

}
bool Depense ::ajout(){
    QSqlQuery query;
    QSqlQuery query1;

    int rowc=0;
    int id1=0;

   QString sql = QString("select * from depense");
           QSqlQuery query2(sql);
           if (query2.isActive()) {
               while (query2.next()) {
                   rowc++;
               }
               for(int i=0;i <= rowc;i++)
               {
                query2.seek(i);
                int value=query2.value("id_depense").toInt();

                id1=qMax(id1,value);
               }
               qDebug()<<id1+1;

           }



   //QString id1=query1.value("id_depense");
  // qDebug()<<id1;
  // QString id2=QString::number(id1);
           QFile file1(facture_depense);
           if (!file1.open(QIODevice::ReadOnly))
              qDebug()<<facture_depense+"url" ;
           QByteArray inByteArray = file1.readAll();

    query.prepare("insert into depense(id_depense,nom_depense,nom_depensier,email_depensier,tel_depensier,date_depense,prix_depense,facture_depense)""values(:id,:nomd,:nom,:email,:tel,:date,:prix,:img)");
    query.bindValue(":id",id1+1);
    query.bindValue(":nomd",nom_depense);
    query.bindValue(":nom",nom_depensier);
    query.bindValue(":email",email_depensier);
    query.bindValue(":tel",tel_depensier);
    query.bindValue(":date",date_depense);
    query.bindValue(":prix",prix_depense);
    query.bindValue(":img",inByteArray);
   return query.exec();
}
QSqlQueryModel* Depense::affichage()
{
  /*  QSqlQuery query1;

    int rowc=0;
    int id=0;

   QString sql = QString("select * from depense");
           QSqlQuery query2(sql);
           if (query2.isActive()) {
               while (query2.next()) {
                   rowc++;
               }
               for(int i=0;i <= rowc;i++)
               {
                query2.seek(i);
                int value=query2.value("id_depense").toInt();

                id=qMax(id,value);
               }
               qDebug()<<id;

           }*/

    QSqlTableModel *model = new QSqlTableModel;
       model->setTable("Depense");
       model->setEditStrategy(QSqlTableModel::OnManualSubmit);
       //model->setFilter("etat_depense='autorise'");
       model->select();
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom depense"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("date"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("prix"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("facture"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("nom depensier"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("email"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("tel"));

    model->setHeaderData(8,Qt::Horizontal,QObject::tr("etat"));

    for(int i=0;i<model->rowCount();i++)
    {
        QString fact= "facture N"+model->data(model->index(i,0)).toString();
  model->setData(model->index(i,4),fact);
    }

    return model;
}
bool Depense ::suprimer(QString sup)
{
    QSqlQuery query;

    query.prepare("Delete from depense Where id_depense=:id");
    query.bindValue(":id",sup);
     return query.exec();
}

bool Depense::modifier(QString ids,QString nom,QString nomd,QString email,QString tel,QString date,QString prix,QString etat){

QSqlQuery q;


q.prepare("update depense set nom_depense = :nom , nom_depensier = :nomd , email_depensier = :email ,tel_depensier = :tel ,date_depense = :date ,prix_depense=:prix,etat_depense=:etat where id_depense = :id");
q.bindValue(":id",ids);
q.bindValue(":nom",nom);
q.bindValue(":nomd",nomd);
q.bindValue(":email",email);
q.bindValue(":tel",tel);
q.bindValue(":date",date);
q.bindValue(":prix",prix);
q.bindValue(":etat",etat);
return q.exec();

}

bool Depense::verif(QString nom,QString prix){

    string test=nom.toStdString();
    int verif=0,i=0,len=test.length();
    while ((verif==0)&&(i<len))
    {if (isdigit(test[i])||(islower(test[0])))
    {
        verif=1;
        qDebug() << test[i];

    }
    i++;}

    string test1=prix.toStdString();
    int b=0,len1=test.length();
    bool verif1=true;
    while ((verif1==true)&&(b<len1))
    {if (QChar::isLetter(test1[b]))
    {
        verif1=false;
        qDebug() <<test1[b];

    }
        else{verif1=true;}
    b++;}
    if ((verif1) && (verif==0))
    {
          return true ;

    }
    else
    {
        return false;
    }
}
QSqlQueryModel* Depense::billan(QString fileName)
{
/*QSqlQueryModel* model=new QSqlQueryModel();
   model->setQuery("select nom_depense,DATE_DEPENSE,prix_depense from depense where etat_depense='autorise'");
model->insertColumns(3,1);
model->insertRows(model->rowCount(QModelIndex()),3);
qDebug()<<model->rowCount();

//model->
  // model->setQuery("select nom_depense,DATE_DEPENSE,prix_depense from depense where etat_depense='autorise' ");*/
    QSqlTableModel *model = new QSqlTableModel;
       model->setTable("Depense");
       model->setEditStrategy(QSqlTableModel::OnManualSubmit);
       model->setFilter("etat_depense='autorise'");
       model->select();
       model->removeColumns(4,5);
       model->removeColumn(0);
       //model->removeColumns(5,7);
    // model->removeColumn(7);
     //model->insertRow(model->rowCount());
     int total=0;
     int id1=0;
     for(int i=0;i<model->rowCount();i++)
     {
         total+=model->data(model->index(i,2)).toInt();
     }
     QSqlTableModel *model1 = new QSqlTableModel;
        model1->setTable("sponsoring");
        model1->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model1->select();
        model1->removeColumn(0);
        model1->removeColumns(2,3);
        if(model->rowCount()<model1->rowCount())
        {
        int nb=model1->rowCount()-model->rowCount();
        model->insertRows(model->rowCount(),nb);
        }
        int nbrow=model->rowCount();
model->insertRow(model->rowCount());
model->setData(model->index(nbrow,2),"total="+QString::number(total));
int total1=0;
for(int i=0;i<model1->rowCount();i++)
{
    total1+=model1->data(model1->index(i,3)).toInt();
}
        if(model->rowCount()<model1->rowCount())
        {
        int nb=model->rowCount()-model1->rowCount();
        model1->insertRows(model1->rowCount(),nb);
        }
        int nbrow1=model1->rowCount();
model1->insertRow(model1->rowCount());
model1->setData(model1->index(nbrow1,3),"total="+QString::number(total1));
      QString strStream;
      QTextStream out(&strStream);

      const int rowCount = model->rowCount();
      const int columnCount =model->columnCount();

      out <<  "<html>\n"
          "<head>\n"
          "<meta Content=\"Text/html; charset=Windows-1251\">\n"
          <<  QString("<title>%1</title>\n").arg("strTitle")
          <<  "</head>\n"
              "<h1>testest</h1>"
          "<body bgcolor=#ffffff link=#5000A0>\n"

          "<table border=1 cellspacing=0 cellpadding=2 >\n";

      // headers
      out << "<tr bgcolor=#f0f0f0><td></td><td border=0 >passif</td><td></td><td></td><td>actif</td></tr>";
      out << "<tr bgcolor=#f0f0f0>";
      //for (int column = 0; column < columnCount; column++)
         // if (!pPublic->tableView->isColumnHidden(column))
            //  out << QString("<th>%1</th>").arg(pPublic->tableView->model()->headerData(column, Qt::Horizontal).toString());
          for(int i=0;i<3;i++)
          {
              out <<"<td>"+model->headerData(i, Qt::Horizontal, Qt::DisplayRole). toString()+"</td>";

          }
          for(int i=0;i<4;i++)
          {
              out <<"<td>"+model1->headerData(i, Qt::Horizontal, Qt::DisplayRole). toString()+"</td>";

          }
      out << "</tr>\n";

      // data table
      for (int row = 0; row < rowCount; row++) {

          out << "<tr>";
          for(int i=0;i<3;i++)
          {
              out <<"<td>"+model->data(model->index(row,i)).toString().remove("DEPENSE")+"</td>";

          }
          for(int i=0;i<4;i++)
          {
              out <<"<td>"+model1->data(model1->index(row,i)).toString().remove("SPONSO")+"</td>";

          }
         // for (int column = 0; column < columnCount; column++) {
              //if (!pPublic->tableView->isColumnHidden(column)) {
                //  QString data = pPublic->tableView->model()->data(pPublic->tableView->model()->index(row, column)).toString().simplified();
               //   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
              //}
         // }
          out << "</tr>\n";
      }
       out << "<tr>";
      for(int i=0;i<3;i++)
      {
           out << "<td> </td>";
      }

      out << "<td> your budget ="+QString::number(total1-total)+ "</td>";
       out << "</tr>\n";
      out <<  "</table>\n"
          "</body>\n"
          "</html>\n";

      QTextDocument *document = new QTextDocument();
      document->setHtml(strStream);

      QPrinter printer1;

      //QPrintDialog *dialog = new QPrintDialog(&printer1, NULL);
     // if (dialog->exec() == QDialog::Accepted) {

         // document->print(&printer);

          printer1.setOutputFormat(QPrinter::PdfFormat);
          fileName=fileName+".pdf";
          printer1.setOutputFileName(fileName);
          qDebug() <<fileName;
          document->print(&printer1);
     // }
      /*const QString htmlFileName = QString("%1/%2").arg("C:/Users/iheb debbech/Desktop/ai").arg("myTable.html");

             QFile file(htmlFileName);

             if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                 QMessageBox::critical(nullptr, QObject::tr("database is open"),
                             QObject::tr("cannot create file.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);


             }

             QTextStream out(&file);

            // const xbLong rowCount = tableView->model()->rowCount();
             //const xbLong columnCount = tableView->model()->columnCount();

             out <<  "<html>\n"
                     "<head>\n"
                     "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                 <<  QString("<title>%1</title>\n").arg('test')
                 <<  "</head>\n"
                     "<body bgcolor=#ffffff link=#5000A0>\n"
                     "<h1>testest</h1>"
                     "<table border=1 cellspacing=0 cellpadding=2>\n";

             // headers
             out << "<tr bgcolor=#f0f0f0>";
             for (int i = 0;i < model->columnCount(); i++)
                 //if (!tableView->isColumnHidden(column))
                     //out << QString("<th>%1</th>").arg(tableView->model()->headerData(column, Qt::Horizontal).toString());
             out << "</tr>\n";
             file.flush();

             // data table
             for (int i= 0; i< model->rowCount(); i++) {
                 out << "<tr>";
                 /*for (int j = 0;j< model->columnCount();j++) {
                     //if (!tableView->isColumnHidden(column)) {
                         QString data = tableView->model()->data(tableView->model()->index(row, column)).toString().simplified();
                         out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                     }
                 }
                 out << "</tr>\n";
             }
               out <<  "</table>\n";
               out <<  "</body>\n";
                out << "</html>\n";

             file.close();
             QTextBrowser editor =out;
                 //QPrinter printer;

                 QPrintDialog *dialog1 = new QPrintDialog(&printer);
                 dialog1->setWindowTitle(("Print Document"));
                 if (editor->textCursor().hasSelection())
                     dialog1->addEnabledOption(QAbstractPrintDialog::PrintSelection);
                 if (dialog1->exec() != QDialog::Accepted)


                 editor->print(&printer);*/
   return model;
}
QSqlQueryModel* Depense::recherche(QString search)
{
    search="'"+search+"'";
    QSqlTableModel *model = new QSqlTableModel;
       model->setTable("Depense");
       model->setEditStrategy(QSqlTableModel::OnManualSubmit);
       model->setFilter("nom_depense="+search +" or nom_depensier=" +search +" or id_depense=" +search +" or prix_depense=" + search +" or etat_depense ="+search);

       model->select();
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom depense"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("date"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("prix"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("facture"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("nom depensier"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("email"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("tel"));

    model->setHeaderData(8,Qt::Horizontal,QObject::tr("etat"));

    for(int i=0;i<model->rowCount();i++)
    {
        QString fact= "facture N"+model->data(model->index(i,0)).toString();
  model->setData(model->index(i,4),fact);
    }

    return model;


}
QSqlQueryModel* Depense::billanweb(QString fileName)
{
/*QSqlQueryModel* model=new QSqlQueryModel();
   model->setQuery("select nom_depense,DATE_DEPENSE,prix_depense from depense where etat_depense='autorise'");
model->insertColumns(3,1);
model->insertRows(model->rowCount(QModelIndex()),3);
qDebug()<<model->rowCount();

//model->
  // model->setQuery("select nom_depense,DATE_DEPENSE,prix_depense from depense where etat_depense='autorise' ");*/
    QSqlTableModel *model = new QSqlTableModel;
       model->setTable("Depense");
       model->setEditStrategy(QSqlTableModel::OnManualSubmit);
       model->setFilter("etat_depense='autorise'");
       model->select();
       model->removeColumns(4,5);
       model->removeColumn(0);
       //model->removeColumns(5,7);
    // model->removeColumn(7);
     //model->insertRow(model->rowCount());
     int total=0;
     int id1=0;
     for(int i=0;i<model->rowCount();i++)
     {
         total+=model->data(model->index(i,2)).toInt();
     }
     QSqlTableModel *model1 = new QSqlTableModel;
        model1->setTable("sponsoring");
        model1->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model1->select();
        model1->removeColumn(0);
        model1->removeColumns(2,3);
        if(model->rowCount()<model1->rowCount())
        {
        int nb=model1->rowCount()-model->rowCount();
        model->insertRows(model->rowCount(),nb);
        }
        int nbrow=model->rowCount();
model->insertRow(model->rowCount());
model->setData(model->index(nbrow,2),"total="+QString::number(total));
int total1=0;
for(int i=0;i<model1->rowCount();i++)
{
    total1+=model1->data(model1->index(i,3)).toInt();
}
        if(model->rowCount()<model1->rowCount())
        {
        int nb=model->rowCount()-model1->rowCount();
        model1->insertRows(model1->rowCount(),nb);
        }
        int nbrow1=model1->rowCount();
model1->insertRow(model1->rowCount());
model1->setData(model1->index(nbrow1,3),"total="+QString::number(total1));
      /*QString strStream;
      QTextStream out(&strStream);

      const int rowCount = model->rowCount();
      const int columnCount =model->columnCount();

      out <<  "<html>\n"
          "<head>\n"
          "<meta Content=\"Text/html; charset=Windows-1251\">\n"
          <<  QString("<title>%1</title>\n").arg("strTitle")
          <<  "</head>\n"
              "<h1>testest</h1>"
          "<body bgcolor=#ffffff link=#5000A0>\n"

          "<table border=1 cellspacing=0 cellpadding=2 >\n";

      // headers
      out << "<tr bgcolor=#f0f0f0><td></td><td border=0 >passif</td><td></td><td></td><td>actif</td></tr>";
      out << "<tr bgcolor=#f0f0f0>";
      //for (int column = 0; column < columnCount; column++)
         // if (!pPublic->tableView->isColumnHidden(column))
            //  out << QString("<th>%1</th>").arg(pPublic->tableView->model()->headerData(column, Qt::Horizontal).toString());
          for(int i=0;i<3;i++)
          {
              out <<"<td>"+model->headerData(i, Qt::Horizontal, Qt::DisplayRole). toString()+"</td>";

          }
          for(int i=0;i<4;i++)
          {
              out <<"<td>"+model1->headerData(i, Qt::Horizontal, Qt::DisplayRole). toString()+"</td>";

          }
      out << "</tr>\n";

      // data table
      for (int row = 0; row < rowCount; row++) {

          out << "<tr>";
          for(int i=0;i<3;i++)
          {
              out <<"<td>"+model->data(model->index(row,i)).toString()+"</td>";

          }
          for(int i=0;i<4;i++)
          {
              out <<"<td>"+model1->data(model1->index(row,i)).toString()+"</td>";

          }
         // for (int column = 0; column < columnCount; column++) {
              //if (!pPublic->tableView->isColumnHidden(column)) {
                //  QString data = pPublic->tableView->model()->data(pPublic->tableView->model()->index(row, column)).toString().simplified();
               //   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
              //}
         // }
          out << "</tr>\n";
      }
       out << "<tr>";
      for(int i=0;i<3;i++)
      {
           out << "<td> </td>";
      }

      out << "<td> your budget ="+QString::number(total1-total)+ "</td>";
       out << "</tr>\n";
      out <<  "</table>\n"
          "</body>\n"
          "</html>\n";

      QTextDocument *document = new QTextDocument();
      document->setHtml(strStream);

      QPrinter printer1;

      //QPrintDialog *dialog = new QPrintDialog(&printer1, NULL);
     // if (dialog->exec() == QDialog::Accepted) {
          //printer1.setOutputFormat(QPrinter::);
          fileName=fileName+".html";
          printer1.setOutputFileName(fileName);
          qDebug() <<fileName;
          document->print(&printer1);

          */
                  const QString htmlFileName = QString("%1").arg(fileName+".html");

                  QFile file(htmlFileName);
qDebug() <<"here";
                  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                      QMessageBox::critical(nullptr, QObject::tr("errot"),
                                  QObject::tr( "cant create file web.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
                  }
                 // QString strStream;
                      //  QTextStream out(&strStream);
                 QTextStream out(&file);
qDebug() <<"here2";

                  const int rowCount = model->rowCount();
                  const int columnCount =model->columnCount();

                  out <<  "<html>\n"
                      "<head>\n"
                      "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                      <<  QString("<title>%1</title>\n").arg("testweb")
                      <<  "</head>\n"
                          "<h1>testest</h1>"
                      "<body bgcolor=#ffffff link=#5000A0>\n"

                      "<table border=1 cellspacing=0 cellpadding=2 >\n";

                  // headers
                  out << "<tr bgcolor=#f0f0f0><td></td><td border=0 >passif</td><td></td><td></td><td>actif</td></tr>";
                  out << "<tr bgcolor=#f0f0f0>";
                  //for (int column = 0; column < columnCount; column++)
                     // if (!pPublic->tableView->isColumnHidden(column))
                        //  out << QString("<th>%1</th>").arg(pPublic->tableView->model()->headerData(column, Qt::Horizontal).toString());
                      for(int i=0;i<3;i++)
                      {
                          out <<"<td>"+model->headerData(i, Qt::Horizontal, Qt::DisplayRole). toString()+"</td>";

                      }
                      for(int i=0;i<4;i++)
                      {
                          out <<"<td>"+model1->headerData(i, Qt::Horizontal, Qt::DisplayRole). toString()+"</td>";

                      }
                  out << "</tr>\n";

                  // data table
                  for (int row = 0; row < rowCount; row++) {

                      out << "<tr>";
                      for(int i=0;i<3;i++)
                      {
                          out <<"<td>"+model->data(model->index(row,i)).toString()+"</td>";

                      }
                      for(int i=0;i<4;i++)
                      {
                          out <<"<td>"+model1->data(model1->index(row,i)).toString()+"</td>";

                      }
                     // for (int column = 0; column < columnCount; column++) {
                          //if (!pPublic->tableView->isColumnHidden(column)) {
                            //  QString data = pPublic->tableView->model()->data(pPublic->tableView->model()->index(row, column)).toString().simplified();
                           //   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                          //}
                     // }
                      out << "</tr>\n";
                  }
                   out << "<tr>";
                  for(int i=0;i<3;i++)
                  {
                       out << "<td> </td>";
                  }

                  out << "<td> your budget ="+QString::number(total1-total)+ "</td>";
                   out << "</tr>\n";
                  out <<  "</table>\n"
                      "</body>\n"
                      "</html>\n";

                  //file.close();


                  //x.open(QIODevice::ReadOnly);
                  //QTextStream in(&file);
                  QString html = out.readAll();
                  qDebug() <<"here3";
                  QTextDocument doc;

                  QPrinter p(QPrinter::HighResolution);
                  p.setResolution(QPrinter::HighResolution);
                 // p.setOutputFileName(fileName+".html");
                  p.setOutputFormat(QPrinter::NativeFormat);
                  //QPrintDialog printDialog(&p);
                  //if (printDialog.exec() == QDialog::Accepted) {
                      //QSizeF paperSize;
                      //paperSize.setWidth(p.width());
                     // paperSize.setHeight(p.height());
                      //doc.setPageSize(paperSize);
                      doc.setHtml(html);
                      doc.print(&p);
//}
return model;
}
QSqlQueryModel* Depense::affichagetri()
{


    QSqlTableModel *model = new QSqlTableModel;
       model->setTable("Depense");
       model->setEditStrategy(QSqlTableModel::OnManualSubmit);
       model->setSort(0,Qt::DescendingOrder);
       //model->setFilter("etat_depense='autorise'");
       model->select();
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom depense"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("date"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("prix"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("facture"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("nom depensier"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("email"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("tel"));

    model->setHeaderData(8,Qt::Horizontal,QObject::tr("etat"));

    for(int i=0;i<model->rowCount();i++)
    {
        QString fact= "facture N"+model->data(model->index(i,0)).toString();
  model->setData(model->index(i,4),fact);
    }

    return model;
}
QSqlQueryModel* Depense::affichagetrinom()
{


    QSqlTableModel *model = new QSqlTableModel;
       model->setTable("Depense");
       model->setEditStrategy(QSqlTableModel::OnManualSubmit);
       model->setSort(1,Qt::AscendingOrder);
       //model->setFilter("etat_depense='autorise'");
       model->select();
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom depense"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("date"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("prix"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("facture"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("nom depensier"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("email"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("tel"));

    model->setHeaderData(8,Qt::Horizontal,QObject::tr("etat"));

    for(int i=0;i<model->rowCount();i++)
    {
        QString fact= "facture N"+model->data(model->index(i,0)).toString();
  model->setData(model->index(i,4),fact);
    }

    return model;
}
/*QSqlQueryModel* Depense::affichagenecessiteux()
{
    int l=0;
    QSqlTableModel *model = new QSqlTableModel;
       model->setTable("necessiteux");
       model->setEditStrategy(QSqlTableModel::OnManualSubmit);
       //model->setFilter("etat_depense='autorise'");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom necessiteux"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("sexe"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("age"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("tel"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("adresse"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("besoin"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("nbfamille"));

    model->setHeaderData(8,Qt::Horizontal,QObject::tr("date"));
    QString sql = QString("select * from necessiteux");
    int rowc=0;
            QSqlQuery query2(sql);
            QSqlQuery query3(sql);
            if (query3.isActive()) {
            if (query2.isActive()) {
                while (query2.next()) {
                    rowc++;
                }
                int a=0;
                QList <int> listc;
                for(int i=0;i <= rowc;i++)
                {
                 query2.seek(i);
                // int value=query2.value("id_depense").toInt();
                  if(query2.value(6).toString()=="sang")
                  {
                      listc.insert(a,i);
                      a++;
                  }
                  }
                qDebug()<<listc;
                int b=0;
                while(b<a)
                {
                    for(int c=0;c<a;c++)
                    {

                        query2.seek(listc[b]);
                        query3.seek(listc[c]);
                        if(query2.value(3).toInt()<query3.value(3).toInt())
                        {
                            int e=listc[b];

                              listc[b]=listc[c];
                              listc[c]=e;
                        }
                        else if(query2.value(3).toInt()==query3.value(3).toInt())
                        {
                        QString date_string_on_db = query2.value(8).toString();
                        QString date_string_on_db1 = query3.value(8).toString();
                        QDate Date = QDate::fromString(date_string_on_db,"dd/MM/yyyy");
                        QDate Date1 = QDate::fromString(date_string_on_db1,"dd/MM/yyyy");
                        if((Date!=Date1) && (Date>Date1))
                        {
                            qDebug()<<"in";
                          int e=listc[b];

                            listc[b]=listc[c];
                            listc[c]=e;
                            //b=b+1;
                           }
                        }
                        int x=a-1;
                        if(c==x)
                        {b++;
                        }
                        }

                      //if
                    }

                for(int d=0;d<a;d++)
                {
                    query2.seek(listc[d]);
                    model->insertRow(l);
                    for(int j=0;j <=8;j++)
                    {
                    model->setData(model->index(l,j),query2.value(j).toString());

                    }
                    l++;
                }
                qDeleteAll(listc.begin(), listc.end());
                listc.clear();

              a=0;
                for(int i=0;i <= rowc;i++)
                {
                 query2.seek(i);
                // int value=query2.value("id_depense").toInt();
                  if(query2.value(6).toString()=="cancer")
                  {
                      listc.insert(a,i);
                      a++;
                  }
                  }
                qDebug()<<listc;
              b=0;
                while(b<a)
                {
                    for(int c=0;c<a;c++)
                    {

                        query2.seek(listc[b]);
                        query3.seek(listc[c]);
                        if(query2.value(3).toInt()<query3.value(3).toInt())
                        {
                            int e=listc[b];

                              listc[b]=listc[c];
                              listc[c]=e;
                        }
                        else if(query2.value(3).toInt()==query3.value(3).toInt())
                        {
                        QString date_string_on_db = query2.value(8).toString();
                        QString date_string_on_db1 = query3.value(8).toString();
                        QDate Date = QDate::fromString(date_string_on_db,"dd/MM/yyyy");
                        QDate Date1 = QDate::fromString(date_string_on_db1,"dd/MM/yyyy");
                        if((Date!=Date1) && (Date>Date1))
                        {
                            qDebug()<<"in";
                          int e=listc[b];

                            listc[b]=listc[c];
                            listc[c]=e;
                            //b=b+1;
                           }
                        }
                        int x=a-1;
                        if(c==x)
                        {b++;
                        }
                        }

                      //if
                    }

                for(int d=0;d<a;d++)
                {
                    query2.seek(listc[d]);
                    model->insertRow(l);
                    for(int j=0;j <=8;j++)
                    {
                    model->setData(model->index(l,j),query2.value(j).toString());

                    }
                    l++;
                }
                qDeleteAll(listc.begin(), listc.end());
                listc.clear();


                /*for(int i=0;i <= rowc;i++)
                {
                 query2.seek(i);
                // int value=query2.value("id_depense").toInt();
                  if(query2.value(6).toString()=="cancer")
                  {
                      model->insertRow(l);
                      for(int j=0;j <=8;j++)
                      {
                      model->setData(model->index(l,j),query2.value(j).toString());

                      }
                      l++;

                  }
                  }*./
                a=0;
                for(int i=0;i <= rowc;i++)
                {
                 query2.seek(i);
                // int value=query2.value("id_depense").toInt();
                  if(query2.value(6).toString()=="faim")
                  {
                      listc.insert(a,i);
                      a++;
                  }
                  }
                qDebug()<<listc;
                b=0;
                while(b<a)
                {
                    for(int c=0;c<a;c++)
                    {

                        query2.seek(listc[b]);
                        query3.seek(listc[c]);
                        if(query2.value(3).toInt()<query3.value(3).toInt())
                        {
                            int e=listc[b];

                              listc[b]=listc[c];
                              listc[c]=e;
                        }
                        else if(query2.value(3).toInt()==query3.value(3).toInt())
                        {
                        QString date_string_on_db = query2.value(8).toString();
                        QString date_string_on_db1 = query3.value(8).toString();
                        QDate Date = QDate::fromString(date_string_on_db,"dd/MM/yyyy");
                        QDate Date1 = QDate::fromString(date_string_on_db1,"dd/MM/yyyy");
                        if((Date!=Date1) && (Date>Date1))
                        {
                            qDebug()<<"in";
                          int e=listc[b];

                            listc[b]=listc[c];
                            listc[c]=e;
                            //b=b+1;
                           }
                        }
                        int x=a-1;
                        if(c==x)
                        {b++;
                        }
                        }

                      //if
                    }

                for(int d=0;d<a;d++)
                {
                    query2.seek(listc[d]);
                    model->insertRow(l);
                    for(int j=0;j <=8;j++)
                    {
                    model->setData(model->index(l,j),query2.value(j).toString());

                    }
                    l++;
                }
                qDeleteAll(listc.begin(), listc.end());
                listc.clear();
                a=0;
                for(int i=0;i <= rowc;i++)
                {
                 query2.seek(i);
                // int value=query2.value("id_depense").toInt();
                  if(query2.value(6).toString()=="diabet")
                  {
                      listc.insert(a,i);
                      a++;
                  }
                  }
                qDebug()<<listc;
                 b=0;
                while(b<a)
                {
                    for(int c=0;c<a;c++)
                    {

                        query2.seek(listc[b]);
                        query3.seek(listc[c]);
                        if(query2.value(3).toInt()<query3.value(3).toInt())
                        {
                            int e=listc[b];

                              listc[b]=listc[c];
                              listc[c]=e;
                        }
                        else if(query2.value(3).toInt()==query3.value(3).toInt())
                        {
                        QString date_string_on_db = query2.value(8).toString();
                        QString date_string_on_db1 = query3.value(8).toString();
                        QDate Date = QDate::fromString(date_string_on_db,"dd/MM/yyyy");
                        QDate Date1 = QDate::fromString(date_string_on_db1,"dd/MM/yyyy");
                        if((Date!=Date1) && (Date>Date1))
                        {
                            qDebug()<<"in";
                          int e=listc[b];

                            listc[b]=listc[c];
                            listc[c]=e;
                            //b=b+1;
                           }
                        }
                        int x=a-1;
                        if(c==x)
                        {b++;
                        }
                        }

                      //if
                    }

                for(int d=0;d<a;d++)
                {
                    query2.seek(listc[d]);
                    model->insertRow(l);
                    for(int j=0;j <=8;j++)
                    {
                    model->setData(model->index(l,j),query2.value(j).toString());

                    }
                    l++;
                }
                qDeleteAll(listc.begin(), listc.end());
                listc.clear();
                a=0;
                for(int i=0;i <= rowc;i++)
                {
                 query2.seek(i);
                // int value=query2.value("id_depense").toInt();
                  if(query2.value(6).toString()=="vetement")
                  {
                      listc.insert(a,i);
                      a++;
                  }
                  }
                qDebug()<<listc;
               b=0;
                while(b<a)
                {
                    for(int c=0;c<a;c++)
                    {

                        query2.seek(listc[b]);
                        query3.seek(listc[c]);
                        if(query2.value(3).toInt()<query3.value(3).toInt())
                        {
                            int e=listc[b];

                              listc[b]=listc[c];
                              listc[c]=e;
                        }
                        else if(query2.value(3).toInt()==query3.value(3).toInt())
                        {
                        QString date_string_on_db = query2.value(8).toString();
                        QString date_string_on_db1 = query3.value(8).toString();
                        QDate Date = QDate::fromString(date_string_on_db,"dd/MM/yyyy");
                        QDate Date1 = QDate::fromString(date_string_on_db1,"dd/MM/yyyy");
                        if((Date!=Date1) && (Date>Date1))
                        {
                            qDebug()<<"in";
                          int e=listc[b];

                            listc[b]=listc[c];
                            listc[c]=e;
                            //b=b+1;
                           }
                        }
                        int x=a-1;
                        if(c==x)
                        {b++;
                        }
                        }

                      //if
                    }

                for(int d=0;d<a;d++)
                {
                    query2.seek(listc[d]);
                    model->insertRow(l);
                    for(int j=0;j <=8;j++)
                    {
                    model->setData(model->index(l,j),query2.value(j).toString());

                    }
                    l++;
                }
                qDeleteAll(listc.begin(), listc.end());
                listc.clear();
                }
}



    return  model;
}*/
