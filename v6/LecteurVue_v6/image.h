#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
using namespace std;

class Image
{
public:
    // Constructor with default parameter values
    Image(unsigned int pRang = 0, string pCategorie = "", string pTitre = "", string pChemin = "");

    // Getter methods
    unsigned int getRang();
    string getCategorie();
    string getTitre();
    string getChemin();

    void afficher(); // Displays all the fields of the image

private:
    unsigned int _rang;    // Rank of the image within the associated diaporama
    string _titre;         // Title of the image
    string _categorie;     // Category of the image (person, animal, object)
    string _chemin;        // Full path to the folder where the image is located
};

#endif // IMAGE_H

