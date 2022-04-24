#ifndef SPONSOR1_H
#define SPONSOR1_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
//mahdi
class Sponsor1
{
public:

    Sponsor1(QString,QString,QString,QString,QString,QString,QString,int);
   Sponsor1();
   Sponsor1(QString,QString,QString,QString,QString,QString,int);
   QSqlQueryModel * afficher();

    QString getid();
    QString getnom();
    QString getprenom();
    QString getemail();
    QString getnumtel();
    QString getadresse();
    QString getdate();
    int getmontant();
    void setid(QString);
    void setnom(QString);
    void setprenom(QString);
    void setemail(QString);
    void setnumtel(QString);
    void setadresse(QString);
    void setdate(QString);
    void setmontant(int);
    bool ajouter();
    bool supprimer (QString);
    bool modifier(QString );
    QSqlQueryModel * afficher_recherche0(QString b);
    QSqlQueryModel * afficher_recherche1(QString b);
    QSqlQueryModel * afficher_recherche2(QString b);
    QSqlQueryModel * afficher_recherche3(QString b);
    QSqlQueryModel * afficher_recherche4(QString b);
    QSqlQueryModel * afficher_recherche5(QString b);
    QSqlQueryModel * afficher_recherche6(QString b);
    QSqlQueryModel * afficher_recherche7(QString b);

QSqlQueryModel * afficher2(QString b);
QSqlQueryModel * count(QString b);
private:
    QString IDENTIFIANT_SPONSOR ,NOM_SPONSOR,PRENOM_SPONSOR,EMAIL_SPONSOR,NUM_TEL_SPONSOR,ADRESSE_SPONSOR,DATE_DEBUT_SPONSOR;
    int MONTANT_SPONSOR;



};






#endif // SPONSOR1_H
