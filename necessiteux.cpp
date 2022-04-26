#include "necessiteux.h"
#include <QString>
#include <QSqlQuery>


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












