#include "diapo.h" // Inclusion du fichier d'en-tête de la classe Diapo

Diapo::Diapo(unsigned int id, string nom, unsigned int vitesse, unsigned int posCourante, unsigned int nbImage)
{
    _id = id; // Initialisation de l'attribut _id avec la valeur passée en paramètre
    _nom = nom; // Initialisation de l'attribut _nom avec la valeur passée en paramètre
    _vitesse = vitesse; // Initialisation de l'attribut _vitesse avec la valeur passée en paramètre
    _posCourante = posCourante; // Initialisation de l'attribut _posCourante avec la valeur passée en paramètre
    _nbImages = nbImage; // Initialisation de l'attribut _nbImages avec la valeur passée en paramètre
}

Diapo::~Diapo()
{
    // Le destructeur ne fait rien dans cette implémentation
}

unsigned int Diapo::getId()
{
    return _id; // Retourne la valeur de l'attribut _id
}

string Diapo::getNom()
{
    return _nom; // Retourne la valeur de l'attribut _nom
}

unsigned int Diapo::getVitesse()
{
    return _vitesse; // Retourne la valeur de l'attribut _vitesse
}

unsigned int Diapo::getPosCourante()
{
    return _posCourante; // Retourne la valeur de l'attribut _posCourante
}

unsigned int Diapo::getNbImages()
{
    return _nbImages; // Retourne la valeur de l'attribut _nbImages
}

void Diapo::setId(unsigned int id)
{
    _id = id; // Modifie la valeur de l'attribut _id avec la valeur passée en paramètre
}

void Diapo::setNom(string nom)
{
    _nom = nom; // Modifie la valeur de l'attribut _nom avec la valeur passée en paramètre
}

void Diapo::setVitesse(unsigned int vitesse)
{
    _vitesse = vitesse; // Modifie la valeur de l'attribut _vitesse avec la valeur passée en paramètre
}

void Diapo::setPosCourante(unsigned int posCourante)
{
    _posCourante = posCourante; // Modifie la valeur de l'attribut _posCourante avec la valeur passée en paramètre
}

void Diapo::setNbImages(unsigned int nbImages)
{
    _nbImages = nbImages; // Modifie la valeur de l'attribut _nbImages avec la valeur passée en paramètre
}
