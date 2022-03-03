#ifndef EVENEMENT_H
#define EVENEMENT_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQueryModel>

class EVENEMENT
{
    QString ID_EVENT ,NOM_EVENT,DATE_EVENT,LOCALISATION,BUDGET_EVENT,NB_POINT;
public:

    EVENEMENT(QString,QString,QString,QString,QString);
    EVENEMENT(QString,QString,QString,QString);
    EVENEMENT ();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString ID_EVENT);
    bool modifier(QString ID_EVENT);
};

#endif // EVENEMENT_H
