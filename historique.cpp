#include "historique.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QObject>
#include <QtDebug>

historique::historique()
{

}
historique::historique(QString operation,QString id,QString nom)
{
this->operation=operation;
this->id=id;
this->nom=nom;

}
void historique::Ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO historique VALUES (HISTORIQUE_SEQ.nextval,sysdate, :operation,:id_s, :nom_s);");
    query.bindValue(":operation",operation);
   query.bindValue(":id_s",id);
    query.bindValue(":nom_s", nom);


   query.exec();

}
QSqlQueryModel * historique::afficher()
{
QSqlQueryModel * model =new QSqlQueryModel();
model->setQuery("select * from historique");

return model;

}
