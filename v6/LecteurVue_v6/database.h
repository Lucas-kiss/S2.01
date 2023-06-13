#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase> // Inclure la classe QSqlDatabase
#include <QSqlQuery> // Inclure la classe QSqlQuery

#define DATABASE_NAME "S2_01" // Définir le nom de la base de données
#define CONNECT_TYPE "QODBC" // Définir le type de connexion

class Database
{
public:
    Database(); // Constructeur
    bool openDataBase(); // Méthode pour ouvrir la connexion à la base de données
    void closeDataBase(); // Méthode pour fermer la connexion à la base de données

private:
    QSqlDatabase mydb; // Objet QSqlDatabase pour la connexion à la base de données
};

#endif // DATABASE_H
