#ifndef DIAPO_H
#define DIAPO_H

#include "image.h"
#include <vector>

typedef std::vector<Image*> Diaporama;   // Structure de données contenant les infos sur les images

class Diapo
{
public:
    Diapo(unsigned int _Id=1,
          string _Nom="", unsigned int _Vitesse=1, unsigned int _posCourante =0,unsigned int _nbImage=0);
    ~Diapo();
    unsigned int getId();
    string getNom();

    unsigned int getVitesse();
    unsigned int getPosCourante();
    unsigned int getNbImages();
    void setId(unsigned int);
    void setNom(string);
    void setVitesse(unsigned int);
    void setPosCourante(unsigned int);
    void setNbImages(unsigned int);

private:
    unsigned int _id;
    string _nom;
    unsigned int _vitesse;
    unsigned int _posCourante;
    unsigned int _nbImages;

};


#endif // DIAPO_H
