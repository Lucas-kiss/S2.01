#ifndef LECTEURVUE_H
#define LECTEURVUE_H
#include "image.h"
#include <vector>
#include <QMainWindow>
#include<QTimer>


QT_BEGIN_NAMESPACE
namespace Ui { class LecteurVue; }
QT_END_NAMESPACE

typedef vector<Image*> Diaporama;   // Structure de données contenant les infos sur les images

class LecteurVue : public QMainWindow
{
    Q_OBJECT

public:
    LecteurVue(QWidget *parent = nullptr);
    ~LecteurVue();
    unsigned int nbImages();    // affiche la taille de _diaporama
    Image* imageCourante();     // retourne le pointeur vers l'image courante
    unsigned int numDiaporamaCourant(); // retourne le numéro du diaporama courant

private:
    Ui::LecteurVue *ui;
    unsigned _numDiaporamaCourant;   // numéro du diaporama courant, par défaut 0
    Diaporama _diaporama;            // pointeurs vers les images du diaporama
    unsigned int _posImageCourante;  /* position, dans le diaporama,
                                        de l'image courante.
                                        Indéfini quand diaporama vide.
                                        Démarre à 0 quand diaporama non vide */
    QTimer timer;
    unsigned const int TPS = 2000; // durer du timer
private:
    void chargerDiaporama();    // charge dans _diaporama les images du _numDiaporamaCourant
    void viderDiaporama();      // vide _diaporama de tous ses objets image et les delete
    void avancer();             // incrémente _posImageCourante, modulo nbImages()
    void reculer();             // décrémente _posImageCourante, modulo nbImages()
    void changerDiaporama(unsigned int pNumDiaporama);    // permet de choisir un diaporama, 0 si aucun diaporama souhaité
    void afficher();            // affiche les informations sur lecteur-diaporama et image courante

public slots:
    void LancerDiapo(); // Slot pour lancer le diaporama en mode automatique
    void ArreterDiapo(); // Slot pour arrêter le mode automatique du diaporama et passer en mode manuel
    void AllerAuSuivant(); // Slot pour passer à l'image suivante dans le diaporama
    void AllerAuPrecedent(); // Slot pour passer à l'image précédente dans le diaporama
    void Quitter(); // Slot pour quitter l'application
    void ChargerDiapo(); // Slot pour charger un diaporama
    void EnleverDiapo(); // Slot pour enlever un diaporama
    void ChangerVitesse(); // Slot pour changer la vitesse du diaporama
    void SeRenseigner(); // Slot pour obtenir des informations supplémentaires
    void SuivantAuto(); // Slot appelé à intervalles réguliers pour passer automatiquement à l'image suivante
    };
#endif // LECTEURVUE_H
