#include "evenement.h"
#include <QString>
#include <QSqlQuery>
#include <string>
#include <string.h>
#include <QSqlQueryModel>
using namespace std;
EVENEMENT::EVENEMENT()
{

}
EVENEMENT::EVENEMENT(QString ID_EVENT,QString NOM_EVENT,QString DATE_EVENT,QString LOCALISATION,QString BUDGET_EVENT)
{
    this->ID_EVENT=ID_EVENT;
    this->NOM_EVENT=NOM_EVENT;
    this->DATE_EVENT=DATE_EVENT;
    this->LOCALISATION=LOCALISATION;
    this->BUDGET_EVENT=BUDGET_EVENT;




}

EVENEMENT::EVENEMENT(QString NOM_EVENT,QString DATE_EVENT,QString LOCALISATION,QString BUDGET_EVENT)
{

    this->NOM_EVENT=NOM_EVENT;
    this->DATE_EVENT=DATE_EVENT;
    this->LOCALISATION=LOCALISATION;
    this->BUDGET_EVENT=BUDGET_EVENT;

}



bool EVENEMENT::ajouter()
{
    QSqlQuery b;

    b.prepare("insert into EVENEMENT(ID_EVENT,NOM_EVENT,DATE_EVENT,LOCALISATION,BUDGET_EVENT,NB_POINT) VALUES (:id,:nom,:date,:localisation,:budget,0)" );
    b.bindValue(":id",ID_EVENT);
    b.bindValue(":nom",NOM_EVENT);
    b.bindValue(":date",DATE_EVENT);
    b.bindValue(":budget",BUDGET_EVENT);

    b.bindValue(":localisation",LOCALISATION);
    string test=NOM_EVENT.toStdString();
        int check=0,i=0,len=test.length();
        while ((check==0)&&(i<len))
        {if (isdigit(test[i]))
        {
            check=1;
        }
        i++;}
        if (check==1)
        {
              return false ;

        }
        else
        {
            return b.exec();
        }



}
bool EVENEMENT::supprimer(QString IDD)
{
    QSqlQuery b;

    b.prepare("Delete from EVENEMENT where ID_EVENT=:IDD");
    b.bindValue(":IDD",IDD);


    return b.exec();
}



QSqlQueryModel * EVENEMENT::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from Evenement");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_EVENT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_EVENT"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATE_EVENT"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("LOCALISATION"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("BUDGET_EVENT"));

    return model;
}
 QSqlQueryModel * EVENEMENT::rechercher(QString rech)
 {
     QSqlQuery b;
     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("SELECT * FROM EVENEMENT where  ID_EVENT='"+rech+"' ");

     return model;




 }




bool EVENEMENT::modifier(QString idd)
{
QSqlQuery b;

b.prepare("update EVENEMENT set NOM_EVENT=:nom ,DATE_EVENT=:date ,BUDGET_EVENT=:budget ,LOCALISATION=:local , nb_point= 0 where ID_EVENT=:idd");

b.bindValue(":idd",idd);
b.bindValue(":nom",NOM_EVENT);
b.bindValue(":date",DATE_EVENT);
b.bindValue(":budget",BUDGET_EVENT);
b.bindValue(":local",LOCALISATION);


return b.exec();
}





//hello
//JUYGGH

