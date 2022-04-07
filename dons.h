#ifndef DONS_H
#define DONS_H

#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>

class DonsData;

class Dons
{

public:
    Dons();
    Dons(QString,QString,QString,QString,QString);
    //getters
    QString getid_don();
    QString getid_donateur();
    QString getquantitee();
    QString gettype_don();
    QString getcathegorie();
    
    //setters
    void setid_don(QString i);
   void setid_donateur(QString i);
    void setquantitee(QString n);
    void settype_don(QString t);
    void setcathegorie(QString a);
    //foctionnalite de base relatives a l entitee etudiant
    bool ajouterd();
    QSqlQueryModel * afficherd();
    bool supprimerd(QString);
    bool modifierd(QString id_don);

    Dons(const Dons &);
    Dons &operator=(const Dons &);
    ~Dons();

private:
      QString id_don,id_donateur ,quantitee,type_don,cathegorie;
    QSharedDataPointer<DonsData> data;
};

#endif // DONS_H
