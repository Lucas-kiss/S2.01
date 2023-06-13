#include "database.h"
#include <QDebug>
#include <QSqlError>

Database::Database()
{

}

bool Database::openDataBase()
{
    mydb = QSqlDatabase::addDatabase(CONNECT_TYPE);
    mydb.setDatabaseName(DATABASE_NAME);
    if(mydb.open()){
        return true;
    }
    else{
        return false;
    }
}

void Database::closeDataBase()
{
    mydb.close();
}


