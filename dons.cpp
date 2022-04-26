#include "dons.h"
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include "connection.h"
#include <string>
#include <string.h>

class DonsData : public QSharedData
{
public:

};

Dons::Dons() : data(new DonsData)
{  id_donateur="" ; quantitee="" ; type_don="" ; cathegorie="" ;}


Dons::Dons(QString id_don,QString id_donateur,QString quantitee,QString type_don,QString cathegorie)
    {this->id_don=id_don;
        this->id_donateur=id_donateur;
         this->quantitee=quantitee;
         this->type_don=type_don;
         this->cathegorie=cathegorie;
    }

    //getters
 QString Dons::getid_don() {return id_don;}
    QString Dons::getid_donateur() {return id_donateur;}
    QString Dons::getquantitee(){return quantitee;}
    QString Dons::gettype_don(){return type_don;}
    QString Dons::getcathegorie(){return cathegorie;}

    //setters
    void Dons::setid_don(QString i){id_don=i;}
   void Dons::setid_donateur(QString i){id_donateur=i;}
    void Dons::setquantitee(QString n){quantitee=n;}
    void Dons::settype_don(QString t){type_don=t;}
    void Dons::setcathegorie(QString a){cathegorie=a;}




bool Dons::ajouterd()
{QSqlQuery query;
    //prepare () prend la requete en parametre pour la preparer  a  execusion
    query.prepare("insert into DONS (id_don, id_donateur, quantitee, type_don, cathegorie) VALUES (:id_don, :id_donateur, :quantitee, :type_don, :cathegorie)");
    //creation des variables liees
    query.bindValue(":id_don",id_don);
    query.bindValue(":id_donateur",id_donateur);
    query.bindValue(":quantitee",quantitee);
    query.bindValue(":type_don",type_don);
    query.bindValue(":cathegorie",cathegorie);

if((id_donateur.isEmpty())||(quantitee.isEmpty())||(id_don.isEmpty()))
{ return false ; }
        else
    return query.exec(); //exec() envoie la requete pour l executer



}
QSqlQueryModel * Dons::afficherd()
    {
        QSqlQueryModel * model=new QSqlQueryModel();
        model->setQuery("select * from DONS");
        model ->setHeaderData(0,Qt::Horizontal,QObject::tr("id_don"));

         model ->setHeaderData(1,Qt::Horizontal,QObject::tr("id_donateur"));
         model ->setHeaderData(2,Qt::Horizontal,QObject::tr("quantitee"));
           model ->setHeaderData(3,Qt::Horizontal,QObject::tr("type_don"));
 model ->setHeaderData(4,Qt::Horizontal,QObject::tr("cathegorie"));
           return model;


}
bool Dons::supprimerd(QString res)
{ QSqlQuery query;

    query.prepare("delete from Dons where id_don = :id  ");
    query.bindValue(":id",res);
    return query.exec();

}
bool Dons::modifierd(QString id_don)
{

        QSqlQuery query;
        //prepare () prend la requete en parametre pour la preparer  a  execusion
        query.prepare("update dons set id_don=:id_don ,id_donateur=:id_donateur ,type_don=:type_don , cathegorie=:cathegorie where id_don=:id_don");
        //creation des variables liees
        query.bindValue(":id_don",id_don);
        query.bindValue(":id_donateur",id_donateur);
        query.bindValue(":type_don",type_don);
        query.bindValue(":cathegorie",cathegorie);


        return query.exec();


    }


Dons::Dons(const Dons &rhs) : data(rhs.data)
{

}

Dons &Dons::operator=(const Dons &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

Dons::~Dons()
{

}
