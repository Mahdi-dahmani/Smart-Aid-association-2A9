#include "avis.h"
#include <QString>
#include <QSqlQuery>
#include <string>
#include <string.h>
#include <QSqlQueryModel>
using namespace std;

avis::avis()
{

}

avis::avis(QString ID_EVENT,QString DESCRIPTION,QString NB_POINT,QString ID_AVIS)
{

    this->ID_AVIS=ID_AVIS;
    this->ID_EVENT=ID_EVENT;
    this->DESCRIPTION=DESCRIPTION;
    this->NB_POINT=NB_POINT;

}


bool avis::ajouter1()
{
    QSqlQuery b;

    b.prepare("insert into AVISS(ID_AVIS, ID_EVENT, DESCRIPTION, NB_POINT) VALUES (:id, :id_event, :description, :nb_point)" );
    b.bindValue(":id",ID_AVIS);
    b.bindValue(":id_event",ID_EVENT);
    b.bindValue(":description",DESCRIPTION);
    b.bindValue(":nb_point",NB_POINT);


return b.exec();
}


QSqlQueryModel * avis::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from AVISS");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NB_POINT"));

    model->setHeaderData(1,Qt::Horizontal,QObject::tr("ID_AVIS"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("ID_EVENT"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("DESCRIPTION"));


    return model;
}


/*bool avis::supprimer(QString IDD)
{
    QSqlQuery b;

    b.prepare("Delete from AVISS where ID_AVIS=:ID");
    b.bindValue(":ID",IDD);


    return b.exec();
}
*/




