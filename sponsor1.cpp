#include "sponsor1.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QString>
#include <QSqlQueryModel>
Sponsor1::Sponsor1()
{
     IDENTIFIANT_SPONSOR="";
     NOM_SPONSOR="";
     PRENOM_SPONSOR="";
     EMAIL_SPONSOR="";
     NUM_TEL_SPONSOR="";
     ADRESSE_SPONSOR="";
     DATE_DEBUT_SPONSOR="";
     MONTANT_SPONSOR=0;
     }
Sponsor1::Sponsor1(QString IDENTIFIANT_SPONSOR,QString NOM_SPONSOR,QString PRENOM_SPONSOR,QString EMAIL_SPONSOR,QString NUM_TEL_SPONSOR,QString ADRESSE_SPONSOR,QString DATE_DEBUT_SPONSOR,int MONTANT_SPONSOR)
{ this->IDENTIFIANT_SPONSOR=IDENTIFIANT_SPONSOR;
    this->NOM_SPONSOR=NOM_SPONSOR;
    this->PRENOM_SPONSOR=PRENOM_SPONSOR;
    this->EMAIL_SPONSOR=EMAIL_SPONSOR;
    this->NUM_TEL_SPONSOR=NUM_TEL_SPONSOR;
    this->ADRESSE_SPONSOR=ADRESSE_SPONSOR;
    this->DATE_DEBUT_SPONSOR=DATE_DEBUT_SPONSOR;
    this->MONTANT_SPONSOR=MONTANT_SPONSOR;
}
Sponsor1::Sponsor1(QString NOM_SPONSOR,QString PRENOM_SPONSOR,QString EMAIL_SPONSOR,QString NUM_TEL_SPONSOR,QString ADRESSE_SPONSOR,QString DATE_DEBUT_SPONSOR,int MONTANT_SPONSOR)
{
    this->NOM_SPONSOR=NOM_SPONSOR;
    this->PRENOM_SPONSOR=PRENOM_SPONSOR;
    this->EMAIL_SPONSOR=EMAIL_SPONSOR;
    this->NUM_TEL_SPONSOR=NUM_TEL_SPONSOR;
    this->ADRESSE_SPONSOR=ADRESSE_SPONSOR;
    this->DATE_DEBUT_SPONSOR=DATE_DEBUT_SPONSOR;
    this->MONTANT_SPONSOR=MONTANT_SPONSOR;
}
QString Sponsor1::getid(){return IDENTIFIANT_SPONSOR ;}
QString Sponsor1::getnom(){return NOM_SPONSOR ;}
QString Sponsor1::getprenom(){return PRENOM_SPONSOR  ;}
QString Sponsor1::getemail(){return EMAIL_SPONSOR  ;}
QString Sponsor1::getnumtel(){return NUM_TEL_SPONSOR ;}
QString Sponsor1::getadresse(){return ADRESSE_SPONSOR;}
QString Sponsor1::getdate(){return DATE_DEBUT_SPONSOR ;}
int Sponsor1::getmontant(){return  MONTANT_SPONSOR;}
void Sponsor1::setid(QString IDENTIFIANT_SPONSOR){this->IDENTIFIANT_SPONSOR=IDENTIFIANT_SPONSOR;}
void Sponsor1::setnom(QString NOM_SPONSOR){this->NOM_SPONSOR=NOM_SPONSOR;}
void Sponsor1::setprenom(QString PRENOM_SPONSOR){this->PRENOM_SPONSOR=PRENOM_SPONSOR;}
void Sponsor1::setemail(QString EMAIL_SPONSOR ){this->EMAIL_SPONSOR=EMAIL_SPONSOR;}
void Sponsor1::setnumtel(QString NUM_TEL_SPONSOR){this->NUM_TEL_SPONSOR=NUM_TEL_SPONSOR;}
void Sponsor1::setadresse(QString ADRESSE_SPONSOR){this->ADRESSE_SPONSOR=ADRESSE_SPONSOR;}
void Sponsor1::setdate(QString DATE_DEBUT_SPONSOR ){this->DATE_DEBUT_SPONSOR =DATE_DEBUT_SPONSOR ;}
void Sponsor1::setmontant(int MONTANT_SPONSOR){this->MONTANT_SPONSOR=MONTANT_SPONSOR;}
bool Sponsor1::ajouter()
{
    QSqlQuery query;


         query.prepare("INSERT INTO SPONSOR (IDENTIFIANT_SPONSOR,NOM_SPONSOR,PRENOM_SPONSOR,EMAIL_SPONSOR, NUM_TEL_SPONSOR, ADRESSE_SPONSOR,DATE_DEBUT_SPONSOR,MONTANT_SPONSOR) "
                       "VALUES (:identifiant_sponsor, :nom_sponsor, :prenom_sponsor,:email_sponsor,:num_tel_sponsor,:adresse_sponsor,:date_debut_sponsor,:montant_sponsor)");
         query.bindValue(":identifiant_sponsor",IDENTIFIANT_SPONSOR);
         query.bindValue(":nom_sponsor", NOM_SPONSOR);
         query.bindValue(":prenom_sponsor", PRENOM_SPONSOR);
         query.bindValue(":email_sponsor", EMAIL_SPONSOR);
         query.bindValue(":num_tel_sponsor", NUM_TEL_SPONSOR);
         query.bindValue(":adresse_sponsor", ADRESSE_SPONSOR);
         query.bindValue(":date_debut_sponsor", DATE_DEBUT_SPONSOR );
         query.bindValue(":montant_sponsor",MONTANT_SPONSOR);

if((NOM_SPONSOR.isEmpty()||!(NOM_SPONSOR.contains(QRegExp("^[A-Za-z]+$"))))||(PRENOM_SPONSOR.isEmpty()||!(PRENOM_SPONSOR.contains(QRegExp("^[A-Za-z]+$"))))||ADRESSE_SPONSOR.isEmpty()||!(IDENTIFIANT_SPONSOR.contains(QRegExp("^[A-Z0-9]+$")))||!(NUM_TEL_SPONSOR.contains(QRegExp("^[0-9]+$")))||(MONTANT_SPONSOR==0))
{
    return false ;
}
    else return query.exec();
}
bool Sponsor1::supprimer(QString IDD)
{
    QSqlQuery b;

    b.prepare("Delete from SPONSOR where IDENTIFIANT_SPONSOR=:IDD");
    b.bindValue(":IDD",IDD);



    return b.exec();
}

QSqlQueryModel * Sponsor1::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from SPONSOR");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDENTIFIANT_SPONSOR"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_SPONSOR"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM_SPONSOR"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL_SPONSOR"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NUM_TEL_SPONSOR"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ADRESSE_SPONSOR"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("DATE_DEBUT_SPONSOR"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("MONTANT_SPONSOR"));

    return model;
}
bool Sponsor1::modifier(QString IDD ){

QSqlQuery query;


query.prepare("update SPONSOR set NOM_SPONSOR=:nom_sponsor , PRENOM_SPONSOR =:prenom_sponsor , EMAIL_SPONSOR =:email_sponsor , NUM_TEL_SPONSOR =:num_tel_sponsor , ADRESSE_SPONSOR=:adresse_sponsor ,DATE_DEBUT_SPONSOR=:date_sponsor ,MONTANT_SPONSOR=:montant_sponsor where IDENTIFIANT_SPONSOR=:IDD ");
query.bindValue(":IDD",IDD);;
query.bindValue(":nom_sponsor", NOM_SPONSOR);
query.bindValue(":prenom_sponsor", PRENOM_SPONSOR);
query.bindValue(":email_sponsor", EMAIL_SPONSOR);
query.bindValue(":num_tel_sponsor", NUM_TEL_SPONSOR);
query.bindValue(":adresse_sponsor", ADRESSE_SPONSOR);
query.bindValue(":date_sponsor", DATE_DEBUT_SPONSOR );
query.bindValue(":montant_sponsor",MONTANT_SPONSOR);

if(NOM_SPONSOR.isEmpty())
{
    return false ;
}
    else return query.exec();
}


QSqlQueryModel * Sponsor1::afficher_recherche0(QString id)
{
    QSqlQueryModel * model =new QSqlQueryModel();


    model->setQuery("SELECT * FROM SPONSOR where IDENTIFIANT_SPONSOR='"+id+"' ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDENTIFIANT_SPONSOR"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_SPONSOR"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM_SPONSOR"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL_SPONSOR"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NUM_TEL_SPONSOR"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ADRESSE_SPONSOR"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("DATE_DEBUT_SPONSOR"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("MONTANT_SPONSOR"));

    return model ;

}

QSqlQueryModel * Sponsor1::afficher_recherche1(QString adresse)
{
    QSqlQueryModel * model =new QSqlQueryModel();


    model->setQuery("SELECT * FROM SPONSOR where  ADRESSE_SPONSOR='"+adresse+"' ");

    return model ;
}
QSqlQueryModel * Sponsor1::afficher_recherche2(QString nom)
{
    QSqlQueryModel * model =new QSqlQueryModel();


    model->setQuery("SELECT * FROM SPONSOR where NOM_SPONSOR='"+nom+"' ");

    return model ;

}
QSqlQueryModel * Sponsor1::afficher_recherche3(QString prenom)
{
    QSqlQueryModel * model =new QSqlQueryModel();


    model->setQuery("SELECT * FROM SPONSOR where PRENOM_SPONSOR='"+prenom+"' ");

    return model ;

}
QSqlQueryModel * Sponsor1::afficher_recherche5(QString tel)
{
    QSqlQueryModel * model =new QSqlQueryModel();


    model->setQuery("SELECT * FROM SPONSOR where NUM_TEL_SPONSOR='"+tel+"' ");

    return model ;

}
QSqlQueryModel * Sponsor1::afficher_recherche4(QString email)
{
    QSqlQueryModel * model =new QSqlQueryModel();


    model->setQuery("SELECT * FROM SPONSOR where EMAIL_SPONSOR='"+email+"' ");

    return model ;

}

QSqlQueryModel * Sponsor1::afficher_recherche6(QString datee)
{
    QSqlQueryModel * model =new QSqlQueryModel();


    model->setQuery("SELECT * FROM SPONSOR where DATE_DEBUT_SPONSOR='"+datee+"' ");

    return model ;

}


QSqlQueryModel * Sponsor1::afficher_recherche7(QString montant)
{
    QSqlQueryModel * model =new QSqlQueryModel();


    model->setQuery("SELECT * FROM SPONSOR where MONTANT_SPONSOR='"+montant+"' ");

    return model ;

}
