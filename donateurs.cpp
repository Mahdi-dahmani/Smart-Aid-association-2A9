#include "donateurs.h"
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include "connection.h"


donateurs::donateurs()
{

}

donateurs::donateurs(QString ID_DONATEUR, QString NOM_DONATEUR, QString TEL_DONATEUR, QString ADRESSE_DONATEUR, QString DON_DONATEUR)
{

this->ID_DONATEUR=ID_DONATEUR ;
this->NOM_DONATEUR=NOM_DONATEUR;
this->TEL_DONATEUR=TEL_DONATEUR ;
 this->ADRESSE_DONATEUR=ADRESSE_DONATEUR;
  this->DON_DONATEUR=DON_DONATEUR;

}
bool donateurs::ajouter()
{
    QSqlQuery query;
    //prepare () prend la requete en parametre pour la preparer  a  execusion
    query.prepare("insert into DONATEURS (ID_DONATEUR ,NOM_DONATEUR ,TEL_DONATEUR,ADRESSE_DONATEUR,DON_DONATEUR ) VALUES (:ID_DONATEUR, :NOM_DONATEUR,:TEL_DONATEUR,:ADRESSE_DONATEUR,:DON_DONATEUR)");
    //creation des variables liees
    query.bindValue(":ID_DONATEUR",ID_DONATEUR);
    query.bindValue(":NOM_DONATEUR",NOM_DONATEUR);
    query.bindValue(":TEL_DONATEUR",TEL_DONATEUR);
    query.bindValue(":ADRESSE_DONATEUR",ADRESSE_DONATEUR);

    query.bindValue(":DON_DONATEUR",DON_DONATEUR);

    return query.exec(); //exec() envoie la requete pour l executer
}
QSqlQueryModel * donateurs::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from donateurs");
    model ->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_DONATEUR"));
     model ->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_DONATEUR"));
      model ->setHeaderData(2,Qt::Horizontal,QObject::tr("TEL_DONATEUR"));
       model ->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESSE_DONATEUR"));
          model ->setHeaderData(4,Qt::Horizontal,QObject::tr("DON_DONATEUR"));
       return model;
}
bool donateurs::supprimer(QString ID_DONATEUR)
{
    QSqlQuery query;
    QString res=QString(ID_DONATEUR);
    query.prepare("delete from donateurs where id_donateur = :ID_DONATEUR");
    query.bindValue(":ID_DONATEUR",res);
    return query.exec();
}
bool donateurs::modifier(QString ID_DONATEURR)
{
    QSqlQuery query;
    //prepare () prend la requete en parametre pour la preparer  a  execusion
    query.prepare("update donateurs set nom_donateur=:nom , tel_donateur=:tel , adresse_donateur=:adresse, don_donateur=:don where id_donateur=:id");
    //creation des variables liees
    query.bindValue(":id",ID_DONATEURR);
    query.bindValue(":nom",NOM_DONATEUR);
    query.bindValue(":tel",TEL_DONATEUR);
    query.bindValue(":adresse",ADRESSE_DONATEUR);
    query.bindValue(":don",DON_DONATEUR);
    return query.exec();


}
