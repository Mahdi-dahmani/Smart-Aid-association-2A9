#ifndef NECESSITEUX_H
#define NECESSITEUX_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QString>
class NECESSITEUX
{
    QString ID_NECESSITEUX,NOM_NECESSITEUX,SEXE,AGE,TEL,ADRESSE,BESOIN,MBR_FAMILLE,DATE_NECESSITEUX;

public:
    NECESSITEUX();
    NECESSITEUX(QString,QString,QString,QString,QString,QString,QString,QString);
    NECESSITEUX(QString,QString,QString,QString,QString,QString,QString,QString,QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool modifier(QString ID_NECESSITEUX);
    bool supprimer(QString ID_NECESSITEUX);
};

#endif // NECESSITEUX_H
