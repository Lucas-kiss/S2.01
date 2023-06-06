#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#define DATABASE_NAME "S2_01"
#define CONNECT_TYPE "QODBC"

class Database
{
public:
    Database();
    bool openDataBase();
    void closeDataBase();
private:
    QSqlDatabase mydb;
};

#endif // DATABASE_H
