#include "image.h"

// Définition du constructeur de la classe Image avec des paramètres
Image::Image(unsigned int pRang, string pCategorie, string pTitre, string pChemin)
{
    // Initialisation des attributs de la classe avec les valeurs des paramètres
    _rang = pRang;
    _categorie = pCategorie;
    _titre = pTitre;
    _chemin = pChemin;
}

// Définition de la méthode getRang() qui retourne la valeur de l'attribut _rang c'est-à-dire le rang de l'image
unsigned int Image::getRang()
{
    return _rang;
}

// Définition de la méthode getCategorie() qui retourne la valeur de l'attribut _categorie c'est-à-dire la catégorie de l'image
string Image::getCategorie()
{
    return _categorie;
}

// Définition de la méthode getTitre() qui retourne la valeur de l'attribut _titre c'est-à-dire le titre de l'image
string Image::getTitre()
{
    return _titre;
}

// Définition de la méthode getChemin() qui retourne la valeur de l'attribut _chemin c'est-à-dire le chemin de l'image
string Image::getChemin()
{
    return _chemin;
}

// Définition de la méthode afficher() qui affiche les informations de l'image
void Image::afficher()
{
    // Affichage des informations sur l'image en utilisant les méthodes get
    cout << "image(rang: " << getRang() << ", titre: " << getTitre() << ", categorie: "
         << getCategorie() << ", chemin: " << getChemin() << ")" << endl;
}
