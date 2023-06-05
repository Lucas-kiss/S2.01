#include "lecteur.h"
#include "image.h"

// Définition du constructeur de la classe Lecteur
Lecteur::Lecteur()
{
    _numDiaporamaCourant = 0;   // Le lecteur est vide, donc le numéro du diaporama courant est initialisé à 0
}

// Définition de la méthode avancer() permettant de passer d'une image à la suivante
void Lecteur::avancer()
{
    // Vérification si la position de l'image courante est à la dernière image
    if (_posImageCourante == nbImages() - 1)
    {
        _posImageCourante = 0;  // Si oui, on passe à la première image
    }
    else
    {
        _posImageCourante = _posImageCourante + 1;  // Sinon, on passe à l'image suivante
    }
}

// Définition de la méthode reculer() permettant de passer d'une image à la précédente
void Lecteur::reculer()
{
    // Vérification si la position de l'image courante est à la première image
    if (_posImageCourante == 0)
    {
        _posImageCourante = nbImages() - 1;  // Si oui, on passe à la dernière image (boucle)
    }
    else
    {
        _posImageCourante = _posImageCourante - 1;  // Sinon, on passe à l'image précédente
    }
}


// Définition de la méthode changerDiaporama() permettant de changer de diaporama
void Lecteur::changerDiaporama(unsigned int pNumDiaporama)
{
    // s'il y a un diaporama courant, le vider, puis charger le nouveau Diaporama
    if (numDiaporamaCourant() > 0)
    {
        viderDiaporama();
    }
    _numDiaporamaCourant = pNumDiaporama;
    if (numDiaporamaCourant() > 0)
    {
        chargerDiaporama(); // charge le diaporama courant
    }

}

// Définition de la méthode chargerDiaporama() permettant de charger les images du diaporama
void Lecteur::chargerDiaporama()
{
    /* Chargement des images associées au diaporama courant
       Dans une version ultérieure, ces données proviendront d'une base de données,
       et correspondront au diaporama choisi */

    // Exemple de chargement d'images
    Image* imageACharger;

    // Création et ajout de l'image "Blanche Neige" au diaporama
    imageACharger = new Image(3, "personne", "Blanche Neige", "C:\\cartesDisney\\carteDisney2.gif");
    _diaporama.push_back(imageACharger);

    // Création et ajout de l'image "Cendrillon" au diaporama
    imageACharger = new Image(2, "personne", "Cendrillon", "C:\\cartesDisney\\carteDisney4.gif");
    _diaporama.push_back(imageACharger);

    // Création et ajout de l'image "Mickey" au diaporama
    imageACharger = new Image(4, "animal", "Mickey", "C:\\cartesDisney\\carteDisney1.gif");
    _diaporama.push_back(imageACharger);

    // Création et ajout de l'image "Grincheux" au diaporama
    imageACharger = new Image(1, "personne", "Grincheux", "C:\\cartesDisney\\carteDisney1.gif");
    _diaporama.push_back(imageACharger);

    // Tri des images dans l'ordre croissant en fonction du rang
    Image* copy;
    for (unsigned int ici = nbImages(); ici > 1; ici--)
    {
        for (unsigned int i = 0; i < ici - 1; ++i)
        {
            // Si l'image actuelle a un rang supérieur à l'image suivante, on les échange
            if (_diaporama[i]->getRang() > _diaporama[i + 1]->getRang())
            {
                copy = _diaporama.at(i);
                _diaporama.at(i) = _diaporama.at(i + 1);
                _diaporama.at(i + 1) = copy;
            }
        }
    }

    // Réinitialisation de la position de l'image courante
    _posImageCourante = 0;

    // Affichage des informations sur le diaporama chargé
    cout << "Diaporama num. " << numDiaporamaCourant() << " sélectionné." << endl;
    cout << nbImages() << " images chargées dans le diaporama." << endl;
}


// Définition de la méthode viderDiaporama() permettant de vider le diaporama
void Lecteur::viderDiaporama()
{
    // Vérification s'il y a des images dans le diaporama
    if (nbImages() > 0)
    {
        unsigned int taille = nbImages();

        // Suppression de toutes les images du diaporama
        for (unsigned int i = 0; i < taille ; i++)
        {
            _diaporama.pop_back(); // Supprime le dernier élément du vecteur (et le détruit)
        }

        // Réinitialisation de la position de l'image courante
        _posImageCourante = 0;
    }

    // Affichage du nombre d'images restantes dans le diaporama
    cout << nbImages() << " images restantes dans le diaporama." << endl;
}


// Définition de la méthode afficher() permettant de charger d'afficher les images du diaporama
void Lecteur::afficher()
{
    /* affiche les information sur le lecteur :
     * 1) vide (si num. de diaporama = 0) OU BIEN  numéro de diaporama affiché
     * 2) Si un diaporama courant est chargé (num. de diaporama > 0), affiche l'image courante OU BIEN 'diaporama vide'
     *     si ce diaporama n'a aucun image */

    // Vérification si un diaporama courant est chargé
    if (numDiaporamaCourant() > 0)
    {
        cout << numDiaporamaCourant() << endl;

        // Vérification si le diaporama contient des images
        if (nbImages() != 0)
        {
            unsigned int taille = nbImages();

            // Affichage de chaque image du diaporama en utilisant la méthode afficher() de la classe Image
            for (unsigned int i = 0; i < taille ; i++)
            {
                _diaporama[i]->afficher();
            }
        }
        else
        {
            cout << "diaporama vide" << endl;
        }
    }
    else
    {
        cout << "vide" << endl;
    }
}


// Définition de la méthode nbImages() permettant retourner de le nombre d'images du diaporama
unsigned int Lecteur::nbImages()
{
    return _diaporama.size();
}

// Définition de la méthode imageCourante() permettant retourner de limage courante du diaporama
Image *Lecteur::imageCourante()
{
    return nullptr;
}

// Définition de la méthode numDiaporamaCourant() permettant retourner de le numéro de l'images courante du diaporama
unsigned int Lecteur::numDiaporamaCourant()
{
    return _numDiaporamaCourant;
}
