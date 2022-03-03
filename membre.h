#ifndef MEMBRE_H
#define MEMBRE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Membre
{
    QString nom,prenom,user,email,mdp,branche,id,nb_point;


public:
    Membre();
    Membre (QString,QString ,QString,QString,QString,QString);
    Membre (QString,QString,QString,QString,QString,QString,QString,QString);

    QString getNom() { return nom;}
    QString getprenom() { return prenom;}
    QString getemail() { return email;}

    void setNom(QString n){nom=n;}
    void setprenom(QString n){prenom=n;}
    void setEmail(QString n){email=n;}


    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString userr);
    bool modifier(QString userr);

};

#endif // MEMBRE_H
