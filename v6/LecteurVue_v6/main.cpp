#include "LecteurVue.h" // Inclusion du fichier d'en-tête de la classe LecteurVue

#include <QApplication> // Inclusion de la classe QApplication

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // Création d'une instance de la classe QApplication

    LecteurVue w; // Création d'une instance de la classe LecteurVue
    w.show(); // Affichage de la fenêtre principale

    return a.exec(); // Exécution de la boucle d'événements de l'application
}

