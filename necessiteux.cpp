#include "necessiteux.h"
#include <QString>
#include <QSqlQuery>
#include <QDate>
#include <QDebug>

#include <qsqltablemodel.h>

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
NECESSITEUX::NECESSITEUX()
{

}

NECESSITEUX::NECESSITEUX(QString ID_NECESSITEUX,QString NOM_NECESSITEUX,QString SEXE,QString AGE,QString TEL,QString ADRESSE,QString BESOIN ,QString MBR_FAMILLE ,QString DATE_NECESSITEUX )
{
    this->ID_NECESSITEUX=ID_NECESSITEUX;
    this->NOM_NECESSITEUX=NOM_NECESSITEUX;
    this->SEXE=SEXE;
    this->AGE=AGE;
    this->TEL=TEL;
    this->ADRESSE=ADRESSE;
    this->BESOIN=BESOIN;
    this->MBR_FAMILLE=MBR_FAMILLE;
    this->DATE_NECESSITEUX=DATE_NECESSITEUX;
}

NECESSITEUX::NECESSITEUX(QString NOM_NECESSITEUX,QString SEXE,QString AGE,QString TEL,QString ADRESSE,QString BESOIN ,QString MBR_FAMILLE ,QString DATE_NECESSITEUX )
{
    this->NOM_NECESSITEUX=NOM_NECESSITEUX;
    this->SEXE=SEXE;
    this->AGE=AGE;
    this->TEL=TEL;
    this->ADRESSE=ADRESSE;
    this->BESOIN=BESOIN;
    this->MBR_FAMILLE=MBR_FAMILLE;
    this->DATE_NECESSITEUX=DATE_NECESSITEUX;


}




bool NECESSITEUX::ajouter()
{
    QSqlQuery b;

    b.prepare("insert into NECESSITEUX(ID_NECESSITEUX,NOM_NECESSITEUX,SEXE,AGE,TEL,ADRESSE,BESOIN,MBR_FAMILLE,DATE_NECESSITEUX) VALUES (:id, :nom, :sexe, :age, :tel, :adresse, :besoin, :mbr, :date)");
    b.bindValue(":id",ID_NECESSITEUX);
    b.bindValue(":nom",NOM_NECESSITEUX);
    b.bindValue(":sexe",SEXE);
    b.bindValue(":age",AGE);
    b.bindValue(":tel",TEL);
    b.bindValue(":adresse",ADRESSE);
    b.bindValue(":besoin",BESOIN);
    b.bindValue(":mbr",MBR_FAMILLE);
    b.bindValue(":date",DATE_NECESSITEUX);


    return b.exec();
}


bool NECESSITEUX::supprimer(QString IDD)
{
    QSqlQuery b;
    b.prepare("Delete from NECESSITEUX where ID_NECESSITEUX=:IDD");
    b.bindValue(":IDD",IDD);


    return b.exec();
}

QSqlQueryModel * NECESSITEUX::afficher()
{
    QSqlQuery b;
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from NECESSITEUX");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_NECESSITEUX"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_NECESSITEUX"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("SEXE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("AGE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("TEL"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ADRESSE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("BESOIN"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("MBR_FAMILLE"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("DATE_NECESSITEUX"));


    return model;


}


bool NECESSITEUX::modifier(QString id){
    QSqlQuery b ;
    b.prepare("update NECESSITEUX set NOM_NECESSITEUX =:nom , SEXE =:sexe , AGE=:age , TEL=:tel , ADRESSE=:adresse ,BESOIN=:besoin , MBR_FAMILLE=:mbr , DATE_NECESSITEUX=:date where ID_NECESSITEUX=:id");
    b.bindValue(":id",ID_NECESSITEUX);
    b.bindValue(":nom",NOM_NECESSITEUX);
    b.bindValue(":sexe",SEXE);
    b.bindValue(":age",AGE);
    b.bindValue(":tel",TEL);
    b.bindValue(":adresse",ADRESSE);
    b.bindValue(":besoin",BESOIN);
    b.bindValue(":mbr",MBR_FAMILLE);
    b.bindValue(":date",DATE_NECESSITEUX);

        return b.exec();

    }


QSqlQueryModel * NECESSITEUX::rechercher(QString rech)
{
    QSqlQuery b ;
    QSqlQueryModel * model=new QSqlQueryModel();
    b.prepare("SELECT * FROM NECESSITEUX where ID_NECESSITEUX = :nom or TEL = :nom");
    b.bindValue(":nom" ,rech);
    b.exec();
    model->setQuery(b);



    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_NECESSITEUX"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_NECESSITEUX"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("SEXE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("AGE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("TEL"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ADRESSE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("BESOIN"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("MBR_FAMILLE"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("DATE_NECESSITEUX"));


    return model;






}




QSqlQueryModel * NECESSITEUX::trier()
{
    QSqlQuery b ;
    QSqlQueryModel * model=new QSqlQueryModel();
    b.prepare("SELECT * FROM NECESSITEUX ORDER BY MBR_FAMILLE ASC ;");

    b.exec();
    model->setQuery(b);



    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_NECESSITEUX"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_NECESSITEUX"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("SEXE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("AGE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("TEL"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ADRESSE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("BESOIN"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("MBR_FAMILLE"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("DATE_NECESSITEUX"));


    return model;

}


QSqlQueryModel* NECESSITEUX::affichagenecessiteux()
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
                //qDeleteAll(listc.begin(), listc.end());
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
               // qDeleteAll(listc.begin(), listc.end());
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
                  }*/
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
                //qDeleteAll(listc.begin(), listc.end());
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
               // qDeleteAll(listc.begin(), listc.end());
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
               // qDeleteAll(listc.begin(), listc.end());
                listc.clear();
                }
}
    return  model;
}






