
#include "connection.h"
//test tutogit

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("testt");
db.setUserName("maram");//inserer nom de l'utilisateur
db.setPassword("maram");//inserer mot de passe de cet utilisateur

if (db.open()) test=true;
test=true;




    return  test;
}
//void Connection::closeConnection(){db.close();}
