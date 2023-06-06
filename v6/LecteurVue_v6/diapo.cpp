#include "diapo.h"

Diapo::Diapo(unsigned int id, string nom, unsigned int vitesse, unsigned int posCourante, unsigned int nbImage)
{
    _id = id;
    _nom = nom;
    _vitesse = vitesse;
    _posCourante= posCourante;
    _nbImages= nbImage;
}

Diapo::~Diapo()
{

}


unsigned int Diapo::getId()
{
    return _id;
}

string Diapo::getNom()
{
    return _nom;
}

unsigned int Diapo::getVitesse()
{
    return _vitesse;
}

unsigned int Diapo::getPosCourante()
{
    return _posCourante;
}

unsigned int Diapo::getNbImages()
{
    return _nbImages;
}

void Diapo::setId(unsigned int id)
{
    _id = id;
}

void Diapo::setNom(string nom)
{
    _nom = nom;
}

void Diapo::setVitesse(unsigned int vitesse)
{
    _vitesse = vitesse;
}

void Diapo::setPosCourante(unsigned int posCourante)
{
    _posCourante = posCourante;
}

void Diapo::setNbImages(unsigned int nbImages)
{
    _nbImages = nbImages;
}
