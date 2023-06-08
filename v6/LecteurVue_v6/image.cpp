#include "image.h" // Inclusion du fichier d'en-tête de la classe Image

Image::Image(unsigned int pRang, string pCategorie, string pTitre, string pChemin)
{
    _rang = pRang; // Initialisation de l'attribut _rang avec la valeur passée en paramètre
    _categorie = pCategorie; // Initialisation de l'attribut _categorie avec la valeur passée en paramètre
    _titre = pTitre; // Initialisation de l'attribut _titre avec la valeur passée en paramètre
    _chemin = pChemin; // Initialisation de l'attribut _chemin avec la valeur passée en paramètre
}

unsigned int Image::getRang()
{
    return _rang; // Retourne la valeur de l'attribut _rang
}

string Image::getCategorie()
{
    return _categorie; // Retourne la valeur de l'attribut _categorie
}

string Image::getTitre()
{
    return _titre; // Retourne la valeur de l'attribut _titre
}

string Image::getChemin()
{
    return _chemin; // Retourne la valeur de l'attribut _chemin
}

void Image::afficher()
{
    cout << "image( rang:" << getRang() << ", titre:" << getTitre() << ", categorie:"
         << getCategorie() << ", chemin:"<< getChemin() << ")" << endl;
}

