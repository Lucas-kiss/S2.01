#ifndef DIAPO_H
#define DIAPO_H

#include "image.h" // Inclure le fichier d'en-tête de la classe Image
#include <vector> // Inclure la bibliothèque vector

typedef std::vector<Image*> Diaporama; // Définir un alias de type pour un vecteur de pointeurs d'Image

class Diapo
{
public:
    // Constructeur avec des valeurs par défaut pour les paramètres
    Diapo(unsigned int _Id = 1, string _Nom = "", unsigned int _Vitesse = 1, unsigned int _posCourante = 0, unsigned int _nbImage = 0);


    // Destructeur
    ~Diapo();

    // Méthodes d'accès (getters)
    unsigned int getId();
    string getNom();
    unsigned int getVitesse();
    unsigned int getPosCourante();
    unsigned int getNbImages();

    // Méthodes de modification (setters)
    void setId(unsigned int);
    void setNom(string);
    void setVitesse(unsigned int);
    void setPosCourante(unsigned int);
    void setNbImages(unsigned int);
private:
    unsigned int _id; // Id du diaporama
    string _nom; // Nom du diaporama
    unsigned int _vitesse; // Vitesse du diaporama
    unsigned int _posCourante; // Position actuelle du diaporama
    unsigned int _nbImages; // Nombre d'images dans le diaporama
};

#endif // DIAPO_H
