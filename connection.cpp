#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("SourceProjet_2A9");
db.setUserName("maissa");//inserer nom de l'utilisateur
db.setPassword("maissa");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
