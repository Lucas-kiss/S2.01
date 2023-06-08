#include "database.h" // Inclusion du fichier d'en-tête de la classe Database
#include <QDebug> // Inclusion de la classe QDebug
#include <QSqlError> // Inclusion de la classe QSqlError

Database::Database()
{
    // Le constructeur ne fait rien dans cette implémentation
}

bool Database::openDataBase()
{
    mydb = QSqlDatabase::addDatabase(CONNECT_TYPE); // Ajoute une connexion de type spécifié à la base de données
    mydb.setDatabaseName(DATABASE_NAME); // Définit le nom de la base de données
    if (mydb.open()) {
        return true; // Si la connexion à la base de données réussit, retourne true
    } else {
        return false; // Si la connexion à la base de données échoue, retourne false
    }
}

void Database::closeDataBase()
{
    mydb.close(); // Ferme la connexion à la base de données
}

