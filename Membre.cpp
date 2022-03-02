#include "membre.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
Membre::Membre()
{

}
Membre::Membre(QString id,QString nom,QString prenom,QString user,QString email,QString mdp,QString branche,QString nb_point){
   this->id=id;
    this ->nom=nom;
    this->prenom=prenom;
    this->user=user;
    this->email=email;
    this->mdp=mdp;
    this->branche=branche;
    this->nb_point=nb_point;
}
Membre::Membre (QString nom,QString prenom,QString email,QString user,QString mdp,QString branche){

    this ->nom=nom;
    this->prenom=prenom;
    this->user=user;
    this->email=email;
    this->mdp=mdp;
    this->branche=branche;




}
bool Membre::ajouter(){

QSqlQuery q;


q.prepare("insert into Membres (ID_MEMBRE,NOM_MEMBRE,PRENOM_MEMBRE,EMAIL_MEMBRE,USERNAME_MEMBRE,MDP_MEMBRE,BRANCHE_MEMBRE,NBPOINTS_MEMBRE) values ( :id, :nom, :prenom, :email, :user, :mdp ,:branche, :nb_point)");
q.bindValue(":id",id);
q.bindValue(":nom",nom);
q.bindValue(":prenom",prenom);
q.bindValue(":email",email);
q.bindValue(":user",user);
q.bindValue(":mdp",mdp);
q.bindValue(":nb_point",nb_point);
q.bindValue(":branche",branche);
return q.exec();

}
bool Membre::supprimer(QString userr){

    QSqlQuery q;


    q.prepare("DELETE FROM membres where username_MEMBRE=:user");
    q.bindValue(":user",userr);
    return q.exec();


}
QSqlQueryModel * Membre::afficher(){

    QSqlQueryModel  * mod=new QSqlQueryModel();
    mod->setQuery("SELECT * FROM Membres");
    mod->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    mod->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    mod->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    mod->setHeaderData(3,Qt::Horizontal,QObject::tr("User"));
    mod->setHeaderData(4,Qt::Horizontal,QObject::tr("Branche"));
    mod->setHeaderData(5,Qt::Horizontal,QObject::tr("NB_point"));
    return mod ;
}
bool Membre::modifier(QString userr){

QSqlQuery q;


q.prepare("update membres set nom_MEMBRE = :nom , prenom_MEMBRE = :prenom , email_MEMBRE = :email ,  mdp_MEMBRE = :mdp , branche_MEMBRE = :branche where username_MEMBRE = :user");

q.bindValue(":nom",nom);
q.bindValue(":prenom",prenom);
q.bindValue(":email",email);
q.bindValue(":user",userr);
q.bindValue(":mdp",mdp);

q.bindValue(":branche",branche);
return q.exec();

}
