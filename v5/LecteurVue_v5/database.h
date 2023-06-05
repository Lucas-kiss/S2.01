#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase> // Inclusion du fichier d'en-tête QSqlDatabase pour utiliser la classe QSqlDatabase
#include <QSqlQuery> // Inclusion du fichier d'en-tête QSqlQuery pour utiliser la classe QSqlQuery

#define DATABASE_NAME "S2_01" // Définition d'une constante symbolique DATABASE_NAME avec la valeur "S2_01"
#define CONNECT_TYPE "QODBC" // Définition d'une constante symbolique CONNECT_TYPE avec la valeur "QODBC"

class Database
{
public:
    Database(); // Déclaration du constructeur par défaut de la classe Database
    bool openDataBase(); // Déclaration de la fonction openDataBase() qui permet d'ouvrir la connexion à la base de données
    void closeDataBase(); // Déclaration de la fonction closeDataBase() qui permet de fermer la connexion à la base de données

private:
    QSqlDatabase mydb; // Déclaration d'une variable mydb de type QSqlDatabase pour stocker la connexion à la base de données

};

#endif // DATABASE_H
