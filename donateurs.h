#ifndef DONATEURS_H
#define DONATEURS_H
#include<QSqlQuery>
#include<QSqlQueryModel>

class donateurs
{
    QString ID_DONATEUR,NOM_DONATEUR,TEL_DONATEUR,ADRESSE_DONATEUR,DON_DONATEUR;
public:
    //constructeurs
    donateurs();
    donateurs(QString,QString,QString,QString,QString);
    donateurs(QString,QString,QString,QString);
    //getters
    QString getid_donateur(){return ID_DONATEUR;}
    QString getnom_donateur(){return NOM_DONATEUR;}
    QString gettel_donateur(){return TEL_DONATEUR;}
    QString getadressee_donateur(){return ADRESSE_DONATEUR;}
    QString getdon_donateur(){return DON_DONATEUR;}
    //setters
   void setid_donateur(QString i){ID_DONATEUR=i;}
    void setnom_donateur(QString n){NOM_DONATEUR=n;}
    void settel_donateur(QString t){TEL_DONATEUR=t;}
    void setadressee_donateur(QString a){ADRESSE_DONATEUR=a;}
     void setdon_donateur(QString d){DON_DONATEUR=d;}

    //foctionnalite de base relatives a l entitee etudiant
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier(QString ID_DONATEUR);
   QSqlQueryModel * rechercher(QString rech);
   bool check (QString nom);
   bool check_tlf(QString nom);
};






#endif // DONATEURH_H
