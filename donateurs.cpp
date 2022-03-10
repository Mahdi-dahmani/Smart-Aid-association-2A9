#include "donateurs.h"
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include "connection.h"
#include <string>
#include <string.h>
using namespace std;

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
donateurs::donateurs(QString nom,QString tel,QString add,QString don){

    this->NOM_DONATEUR=nom;
    this->TEL_DONATEUR=tel ;
     this->ADRESSE_DONATEUR=add;
      this->DON_DONATEUR=don;



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
if((NOM_DONATEUR.isEmpty()&&!(NOM_DONATEUR.contains(QRegExp("^[A-Za-z]+$"))))||(ADRESSE_DONATEUR.isEmpty()&&!(ADRESSE_DONATEUR.contains(QRegExp("^[A-Za-z]+$")))))
{ return false ; }
        else
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
    query.prepare("update donateurs set NOM_DONATEUR=:NOM_DONATEUR , TEL_DONATEUR=:TEL_DONATEUR , ADRESSE_DONATEUR=:ADRESSE_DONATEUR, DON_DONATEUR=:DON_DONATEUR where ID_DONATEUR=:ID_DONATEUR");
    //creation des variables liees
    query.bindValue(":ID_DONATEUR",ID_DONATEURR);
    query.bindValue(":NOM_DONATEUR",NOM_DONATEUR);
    query.bindValue(":TEL_DONATEUR",TEL_DONATEUR);
    query.bindValue(":ADRESSE_DONATEUR",ADRESSE_DONATEUR);
    query.bindValue(":DON_DONATEUR",DON_DONATEUR);
    return query.exec();


}
QSqlQueryModel * donateurs::rechercher(QString rech){

    QSqlQuery q;
        QSqlQueryModel  * mod=new QSqlQueryModel();
    q.prepare("SELECT * FROM donateurs where id_donateur = :mot or nom_donateur = :mot or tel_donateur= :mot or adresse_donateur=:mot or don_donateur=:mot ");
    q.bindValue(":mot",rech);
    q.exec();
    mod->setQuery(q);


        mod->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
        mod->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_donateur"));
        mod->setHeaderData(2,Qt::Horizontal,QObject::tr("Tel_donateur"));
        mod->setHeaderData(3,Qt::Horizontal,QObject::tr("Adresse_donateur"));
        mod->setHeaderData(4,Qt::Horizontal,QObject::tr("Don_donateur"));

        return mod ;



}
bool donateurs::check(QString nom)
{




    string test=nom.toStdString();
        int check=0,i=0,len=test.length();
        while ((check==0)&&(i<len))
        {if (isdigit(test[i])||(islower(test[0])))
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
            return true;
        }
}
bool donateurs::check_tlf(QString nom)
{




    string test=nom.toStdString();
        int check=0,i=0,len=test.length();
        while ((check==0)&&(i<len))
        {if (!isdigit(test[i]))
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
            return true;
        }
}
