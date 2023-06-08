#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>     // Include the QSqlDatabase class
#include <QSqlQuery>        // Include the QSqlQuery class

#define DATABASE_NAME "nodenot_bd9"     // Define the name of the database
#define CONNECT_TYPE "QODBC"             // Define the connection type

class Database
{
public:
    Database();                         // Constructor
    bool openDataBase();                // Method to open the database connection
    void closeDataBase();               // Method to close the database connection

private:
    QSqlDatabase mydb;                  // QSqlDatabase object for the database connection
};

#endif // DATABASE_H

