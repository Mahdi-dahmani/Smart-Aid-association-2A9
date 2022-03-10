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
    QSqlQueryModel * rechercher(QString rech);
bool recherchertt(QString rech);
bool check(QString nom);
bool check_branche(QString branche);
bool check_mdp(QString nom);
};

#endif // MEMBRE_H
