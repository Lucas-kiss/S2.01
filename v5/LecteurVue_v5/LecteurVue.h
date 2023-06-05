#ifndef LECTEURVUE_H
#define LECTEURVUE_H
#include "image.h"
#include "database.h"
#include <vector>
#include <QMainWindow>
#include<QTimer>


#define CHEMIN "F:/Documents/IUT/A1/S2.01/v5/LecteurVue_v5/ressources"

QT_BEGIN_NAMESPACE
namespace Ui { class LecteurVue; }
QT_END_NAMESPACE


typedef vector<Image*> Diaporama; // Structure de données contenant les infos sur les images

class LecteurVue : public QMainWindow
{
    Q_OBJECT

public:
    LecteurVue(QWidget *parent = nullptr);
    ~LecteurVue();
    unsigned int nbImages();    // affiche la taille de _diaporama
    Image* imageCourante();     // retourne le pointeur vers l'image courante
    unsigned int numDiaporamaCourant();

private:
    Ui::LecteurVue *ui;
    unsigned _numDiaporamaCourant;   // numéro du diaporama courant, par défaut 0
    Diaporama _diaporama;            // pointeurs vers les images du diaporama
    unsigned int _posImageCourante;  /* position, dans le diaporama,
                                        de l'image courante.
                                        Indéfini quand diaporama vide.
                                        Démarre à 0 quand diaporama non vide */
    QTimer timer;
    unsigned int TPS = 2000;// durer du timer
    bool vider = false; // indicateur pour afficher les element graphiques
    Database *db; // pointeur vers la classe database
    QString nomDiapo; //nom du dipoarama

private:
    void chargerDiaporama();    // charge dans _diaporama les images du _numDiaporamaCourant
    void viderDiaporama();      // vide _diaporama de tous ses objets image et les delete
    void majLabel(bool);
    unsigned int getVitesse();          // retourne la vitesse à laquelle défile les diapositives
    void setVitesse(unsigned int);      // change la vitesse à laquelle défile les diapositives selon l'entier donné
    void avancer();             // incrémente _posImageCourante, modulo nbImages()
    void reculer();             // décrémente _posImageCourante, modulo nbImages()
    void changerDiaporama(unsigned int pNumDiaporama);    // permet de choisir un diaporama, 0 si aucun diaporama souhaité
    void afficher();            // affiche les informations sur lecteur-diaporama et image courante

public slots:
    void LancerDiapo();
    void ArreterDiapo();
    void AllerAuSuivant();
    void AllerAuPrecedent();
    void SuivantAuto();
    void Quitter();
    void ChargerDiapo();
    void EnleverDiapo();
    void ChangerVitesse();
    void SeRenseigner();
   };
#endif // LECTEURVUE_H
