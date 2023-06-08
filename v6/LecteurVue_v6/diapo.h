#ifndef DIAPO_H
#define DIAPO_H

#include "image.h"      // Include the Image class header file
#include <vector>       // Include the vector library

typedef std::vector<Image*> Diaporama;   // Define a type alias for a vector of Image pointers

class Diapo
{
public:
    // Constructor with default parameter values
    Diapo(unsigned int _Id = 1, string _Nom = "", unsigned int _Vitesse = 1, unsigned int _posCourante = 0, unsigned int _nbImage = 0);

    // Destructor
    ~Diapo();

    // Getter methods
    unsigned int getId();
    string getNom();
    unsigned int getVitesse();
    unsigned int getPosCourante();
    unsigned int getNbImages();

    // Setter methods
    void setId(unsigned int);
    void setNom(string);
    void setVitesse(unsigned int);
    void setPosCourante(unsigned int);
    void setNbImages(unsigned int);

private:
    unsigned int _id;               // Id of the diapo
    string _nom;                    // Name of the diapo
    unsigned int _vitesse;          // Speed of the diapo
    unsigned int _posCourante;      // Current position of the diapo
    unsigned int _nbImages;         // Number of images in the diapo
};

#endif // DIAPO_H

