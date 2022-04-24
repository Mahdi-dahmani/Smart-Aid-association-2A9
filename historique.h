#ifndef HISTORIQUE_H
#define HISTORIQUE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class historique
{
public:
    historique();
    historique(QString,QString id,QString nom);
    void Ajouter();
    QSqlQueryModel * afficher();
private:
    QString operation,id,nom;

};

#endif // HISTORIQUE_H
