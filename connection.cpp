
#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("source_projet_2A9");
db.setUserName("mahdi");//inserer nom de l'utilisateur
db.setPassword("7122019");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
