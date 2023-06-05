#include "database.h"
#include <QDebug>
#include <QSqlError>

Database::Database()
{
    // Constructeur par défaut de la classe Database
}

bool Database::openDataBase()
{
    mydb = QSqlDatabase::addDatabase(CONNECT_TYPE);
    mydb.setDatabaseName(DATABASE_NAME);

    if (mydb.open()) {
        // La base de données a été ouverte avec succès
        return true;
    } else {
        // Une erreur s'est produite lors de l'ouverture de la base de données
        qDebug() << "Erreur lors de l'ouverture de la base de données:" << mydb.lastError().text();
        return false;
    }
}

void Database::closeDataBase()
{
    mydb.close();
}


