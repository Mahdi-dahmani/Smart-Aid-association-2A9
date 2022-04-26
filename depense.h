#ifndef DEPENSE_H
#define DEPENSE_H
#include <QSqlQuery>
#include <QString>
#include <QSqlQueryModel>
 class Depense
{
    public:

    QString nom_depense;
    QString nom_depensier;
    QString email_depensier;
    QString tel_depensier;
    QString date_depense;
    QString prix_depense;
    QString facture_depense;
    QString etat_depense;
    Depense(QString,QString,QString,QString,QString,QString,QString);
    Depense();
    bool ajout();
    bool verif(QString nom,QString prix);

    bool suprimer(QString sup);
    QSqlQueryModel* affichage();
    QSqlQueryModel* affichagetri();
    QSqlQueryModel* affichagetrinom();
    QSqlQueryModel* recherche(QString search);
    QSqlQueryModel* billan(QString fileName);
    QSqlQueryModel* billanweb(QString fileName);
    bool modifier(QString ids,QString nom,QString nomd,QString email,QString tel,QString date,QString prix,QString etat);
     void img();
     //QSqlQueryModel* affichagenecessiteux();
   // bool insertIntoTable(const QVariantList &data);
        //bool insertIntoTable(const QString &name, const QByteArray &pic);
};
#endif // DEPENSE_H
