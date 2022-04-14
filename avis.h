#ifndef AVIS_H
#define AVIS_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQueryModel>

class avis
{
     QString ID_AVIS, ID_EVENT, DESCRIPTION, NB_POINT;
public:

     avis(QString,QString,QString,QString);
     avis();
         bool ajouter1();
         QSqlQueryModel * afficher();
         bool supprimer(QString ID_Avis);

};

#endif // AVIS_H
