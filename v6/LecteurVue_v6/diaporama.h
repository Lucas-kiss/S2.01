#ifndef DIAPORAMA_H
#define DIAPORAMA_H
#include "image.h"
#include <vector>
#include <QCoreApplication>

typedef vector<Image*> Diaporama;   // Structure de données contenant les infos sur les images


class Diapo
{
public:
    Diapo();
    QString getNom();
    unsigned int getNbImages();    // affiche la taille de _diaporama
    Image* imageCourante();     // retourne le pointeur vers l'image courante
    unsigned int numDiaporamaCourant();
    unsigned int getPosImageCourante();
    void setPosImageCourante();

private:
    QString _nomDiapo;
    unsigned _numDiaporamaCourant;   // numéro du diaporama courant, par défaut 0
    unsigned int _posImageCourante;  /* position, dans le diaporama,
                                        de l'image courante.
                                        Indéfini quand diaporama vide.
                                        Démarre à 0 quand diaporama non vide */
};

#endif // DIAPORAMA_H
