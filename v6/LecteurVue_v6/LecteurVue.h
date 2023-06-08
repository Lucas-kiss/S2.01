#ifndef LECTEURVUE_H
#define LECTEURVUE_H

#include "database.h" // Inclusion du fichier d'en-tête de la classe Database
#include <QMainWindow>
#include <QTimer>
#include "choixDiapo.h" // Inclusion du fichier d'en-tête de la classe choixDiapo
#include "diapo.h" // Inclusion du fichier d'en-tête de la classe Diapo

#define CHEMIN "F:/Documents/IUT/A1/S2.01/v6/LecteurVue_v6/ressources" // Définition d'une constante CHEMIN

QT_BEGIN_NAMESPACE
namespace Ui { class LecteurVue; }
QT_END_NAMESPACE

class LecteurVue : public QMainWindow
{
    Q_OBJECT

public:
    LecteurVue(QWidget *parent = nullptr); // Constructeur de la classe LecteurVue
    ~LecteurVue(); // Destructeur de la classe LecteurVue

private:
    Ui::LecteurVue *ui; // Interface utilisateur de la fenêtre LecteurVue
    Diaporama _diaporama; // Instance de la classe Diaporama pour stocker les images du diaporama
    QTimer timer; // Timer pour le défilement automatique des diapositives
    unsigned int TPS = 2000; // Temps entre chaque diapositive en millisecondes
    bool vider = false; // Indicateur si le diaporama est vide ou non
    Database *db; // Pointeur vers une instance de la classe Database pour gérer la base de données
    Diapo *diapo; // Pointeur vers une instance de la classe Diapo pour gérer les diaporamas

private:
    void chargerDiaporama(); // Charge les images du diaporama dans l'instance _diaporama
    void viderDiaporama(); // Vide le diaporama en supprimant toutes les images et en libérant la mémoire
    void majLabel(bool); // Met à jour les étiquettes dans l'interface utilisateur en fonction du paramètre booléen
    unsigned int getVitesse(); // Retourne la vitesse actuelle du défilement des diapositives
    void setVitesse(unsigned int); // Modifie la vitesse du défilement des diapositives en fonction de la valeur donnée
    void avancer(); // Passe à la diapositive suivante dans le diaporama
    void reculer(); // Revient à la diapositive précédente dans le diaporama
    void changerDiaporama(unsigned int pNumDiaporama); // Permet de choisir un diaporama en spécifiant son numéro, 0 pour aucun diaporama sélectionné
    void afficher(); // Affiche les informations sur le lecteur diaporama et l'image courante

public slots:
    void LancerDiapo(); // Slot pour lancer le défilement automatique des diapositives
    void ArreterDiapo(); // Slot pour arrêter le défilement automatique des diapositives
    void AllerAuSuivant(); // Slot pour passer à la diapositive suivante
    void AllerAuPrecedent(); // Slot pour revenir à la diapositive précédente
    void SuivantAuto(); // Slot pour passer à la diapositive suivante automatiquement
    void Quitter(); // Slot pour quitter l'application
    void ChargerDiapo(); // Slot pour charger un diaporama à partir de la base de données
    void EnleverDiapo(); // Slot pour supprimer un diaporama de la base de données
    void ChangerVitesse(); // Slot pour changer la vitesse de défilement des diapositives
    void SeRenseigner(); // Slot pour afficher des informations sur le lecteur diaporama

   };
#endif // LECTEURVUE_H
