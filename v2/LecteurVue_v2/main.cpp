#include "LecteurVue.h" // Inclusion du fichier d'en-tête de la classe LecteurVue
#include <QApplication> // Inclusion de la classe QApplication

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // Création de l'instance de l'application Qt
    LecteurVue w; // Création de l'instance de la fenêtre LecteurVue
    w.show(); // Affichage de la fenêtre
    return a.exec(); // Exécution de la boucle d'événements Qt
}
