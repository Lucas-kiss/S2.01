#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
using namespace std;

class Image
{
public:
    Image(unsigned int pRang=0,
          string pCategorie="", string pTitre="", string pChemin = "");     // constructeur
    unsigned int getRang();                                                 // retourne le rang de l'image
    string getCategorie();                                                  // retourne la catégorie l'image
    string getTitre();                                                      // retourne le titre l'image
    string getChemin();                                                     // retourne le chemin pour obtenir l'image
    void afficher();                                                        // affiche tous les champs de l'image

private:
    unsigned int _rang;         /* rang de l'image au sein du diaporama
                                   auquel l'image est associée */
    string _titre;              // intitulé de l'image
    string _categorie;          // catégorie de l'image (personne, animal, objet)
    string _chemin;             // chemin complet vers le dossier où se trouve l'image
};

#endif // IMAGE_H
