#include "LecteurVue.h" // Inclusion du fichier d'en-tête de la classe LecteurVue
#include "ui_LecteurVue.h" // Inclusion du fichier d'en-tête généré par l'outil de conception Qt

#include <QApplication> // Inclusion de la classe QApplication
#include<QMessageBox>   // Inclusion de la classe QMessageBox

LecteurVue::LecteurVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LecteurVue)
{
    ui->setupUi(this); // Configuration de l'interface utilisateur de la fenêtre

    // Connexion des signaux (interactions de l'utilisateur) aux slots correspondants
    QObject::connect( ui->bLancerDiapo, SIGNAL(clicked()), this, SLOT(LancerDiapo()) );
    QObject::connect( ui->bArreterDiapo, SIGNAL(clicked()), this, SLOT(ArreterDiapo()) );
    QObject::connect( ui->bSuivant, SIGNAL(clicked()), this, SLOT(AllerAuSuivant()) );
    QObject::connect( ui->bPrecedent, SIGNAL(clicked()), this, SLOT(AllerAuPrecedent()) );
    QObject::connect( ui->actionQuitter, SIGNAL(triggered()), this, SLOT(Quitter()) );
    QObject::connect( ui->actionCharger_diaporama, SIGNAL(triggered()), this, SLOT(ChargerDiapo()) );
    QObject::connect( ui->actionEnlever_diaporama, SIGNAL(triggered()), this, SLOT(EnleverDiapo()) );
    QObject::connect( ui->actionVitesse_de_defilement, SIGNAL(triggered()), this, SLOT(ChangerVitesse()) );
    QObject::connect( ui->actionA_propos_de, SIGNAL(triggered()), this, SLOT(SeRenseigner()) );

    // Exemple de chargement d'images
    Image* imageACharger;

    // Création et ajout de l'image "Blanche Neige" au diaporama
    imageACharger = new Image(1, "personne", "Blanche Neige", "..\\LecteurVue_v2\\ressources\\cartesDisney\\disney_19.gif");
    _diaporama.push_back(imageACharger);

    // Création et ajout de l'image "Cendrillon" au diaporama
    imageACharger = new Image(2, "personne","Cendrillon" ,"..\\LecteurVue_v2\\ressources\\cartesDisney\\disney_4.gif");
    _diaporama.push_back(imageACharger);

    // Création et ajout de l'image "Mickey" au diaporama
    imageACharger = new Image(3, "animal", "Mickey", "..\\LecteurVue_v2\\ressources\\cartesDisney\\disney_1.gif");
    _diaporama.push_back(imageACharger);

    // Création et ajout de l'image "Grincheux" au diaporama
    imageACharger = new Image(4, "personne", "Grincheux", "..\\LecteurVue_v2\\ressources\\cartesDisney\\disney_2.gif");
    _diaporama.push_back(imageACharger);


    statusBar()->showMessage(tr("Mode Manuel")); // Affichage d'un message dans la barre de statut


   (*this)._posImageCourante = 0; // Initialise la position courante de l'image à 0
   _numDiaporamaCourant = 1;    // Initialise numéro du diaporama courant à 1
   afficher();
}
LecteurVue::~LecteurVue()
{
    delete ui; // Supprime l'interface utilisateur
}

void LecteurVue::LancerDiapo()
{
    statusBar()->showMessage(tr("Mode auto")); // Affiche "Mode auto" dans la barre de statut
    qDebug() << "Lancer diapo fonctionnel" << Qt::endl; // Affiche un message de débogage
}

void LecteurVue::ArreterDiapo()
{
    qDebug() << "Arreter Diapo fonctionnel" << Qt::endl; // Affiche un message de débogage
}

void LecteurVue::AllerAuSuivant()
{
    statusBar()->showMessage(tr("Mode Manuel")); // Affiche "Mode Manuel" dans la barre de statut
    avancer(); // Appelle la fonction avancer() pour passer à l'image suivante
    afficher(); // Appelle la fonction afficher() pour afficher les informations sur l'image courante
}

void LecteurVue::AllerAuPrecedent()
{
    statusBar()->showMessage(tr("Mode Manuel")); // Affiche "Mode Manuel" dans la barre de statut
    reculer(); // Appelle la fonction reculer() pour revenir à l'image précédente
    afficher(); // Appelle la fonction afficher() pour afficher les informations sur l'image courante
}

void LecteurVue::Quitter()
{
    this->close(); // Ferme la fenêtre
}

void LecteurVue::ChargerDiapo()
{
    qDebug() << "Charger la Diapo fonctionnel" << Qt::endl; // Affiche un message de débogage
}

void LecteurVue::EnleverDiapo()
{
    qDebug() << "Enlever la Diapo fonctionnel" << Qt::endl; // Affiche un message de débogage
}

void LecteurVue::ChangerVitesse()
{
    qDebug() << "Changer la Vitesse fonctionnel" << Qt::endl; // Affiche un message de débogage
}

void LecteurVue::SeRenseigner()
{
    QMessageBox msgBox;
    msgBox.setText("Version: v2\nDate de Creation : 03/05/2023 \nAuteurs : KISS Lucas/DUBOS Lucie");
    msgBox.exec(); // Affiche une boîte de message contenant des informations sur la version, la date de création et les auteurs du programme
}


void LecteurVue::avancer()
{
    if ((*this)._posImageCourante == nbImages() - 1) // Si on est à la dernière image du diaporama
    {
        (*this)._posImageCourante = 0; // Passer à la première image
    }
    else
    {
        (*this)._posImageCourante = (*this)._posImageCourante + 1; // Passer à l'image suivante
    }
}

void LecteurVue::reculer()
{
    if ((*this)._posImageCourante == 0) // Si on est à la première image du diaporama
    {
        (*this)._posImageCourante = nbImages() - 1; // Passer à la dernière image
    }
    else
    {
        (*this)._posImageCourante = (*this)._posImageCourante - 1; // Passer à l'image précédente
    }
}

void LecteurVue::changerDiaporama(unsigned int pNumDiaporama)
{
    // s'il y a un diaporama courant, le vider, puis charger le nouveau Diaporama
    if (numDiaporamaCourant() > 0)
    {
        viderDiaporama(); // Vider le diaporama courant
    }
    _numDiaporamaCourant = pNumDiaporama; // Changer le numéro du diaporama courant
    if (numDiaporamaCourant() > 0)
    {
        chargerDiaporama(); // Charger le diaporama courant
    }
}

void LecteurVue::chargerDiaporama()
{
    // Chargement des images associées au diaporama courant

    // Création d'objets Image et ajout au diaporama
    Image* imageACharger;
    imageACharger = new Image(3, "personne", "Blanche Neige", "C://cartesDisney//carteDisney2.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(2, "personne", "Cendrillon", "C://cartesDisney//carteDisney4.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(4, "animal", "Mickey", "C://cartesDisney//carteDisney1.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(1, "personne", "Grincheux", "C://cartesDisney//carteDisney1.gif");
    _diaporama.push_back(imageACharger);

    Image* copy;
    // Tri du diaporama par rang croissant
    for (unsigned int ici = nbImages(); ici > 1; ici--) {
        for (unsigned int i = 0; i < ici - 1; ++i) {
            if ((*this)._diaporama[i]->getRang() > (*this)._diaporama[i + 1]->getRang())
            {
                cout << "test" << endl;
                copy = (*this)._diaporama.at(i);
                (*this)._diaporama.at(i) = (*this)._diaporama.at(i + 1);
                (*this)._diaporama.at(i + 1) = copy;
            }
        }
    }

    (*this)._posImageCourante = 0; // Réinitialiser la position de l'image courante

    cout << "Diaporama num. " << numDiaporamaCourant() << " selectionne. " << endl;
    cout << nbImages() << " images chargees dans le diaporama" << endl;
}

void LecteurVue::viderDiaporama()
{
    if (nbImages() > 0) // S'il y a des images dans le diaporama
    {
        unsigned int taille = nbImages();
        for (unsigned int i = 0; i < taille; i++)
        {
            _diaporama.pop_back(); // Supprimer le dernier élément du diaporama (et libérer la mémoire)
        }
        _posImageCourante = 0; // Réinitialiser la position de l'image courante
    }
    cout << nbImages() << " images restantes dans le diaporama." << endl;
}

void LecteurVue::afficher()
{
    if (numDiaporamaCourant() > 0)
    {
        cout << numDiaporamaCourant() << endl << nbImages() << endl << _posImageCourante << endl;
        if (nbImages() != 0)
        {
            // Affichage des informations sur l'image courante dans l'interface utilisateur
            ui->lRang->setText((QString::number(_diaporama[_posImageCourante]->getRang())));
            ui->lImage->setPixmap(QPixmap(QString::fromStdString(_diaporama[_posImageCourante]->getChemin())));
            ui->lImage->setAlignment(Qt::AlignCenter);
            ui->lCategorie->setText(QString::fromStdString(_diaporama[_posImageCourante]->getCategorie()));
            ui->lTitre->setText((QString::fromStdString(_diaporama[_posImageCourante]->getTitre())));
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

unsigned int LecteurVue::nbImages()
{
    return _diaporama.size(); // Retourne le nombre d'images dans le diaporama
}

Image* LecteurVue::imageCourante()
{
    return nullptr; // À implémenter : retourner l'image courante
}

unsigned int LecteurVue::numDiaporamaCourant()
{
    return _numDiaporamaCourant; // Retourne le numéro du diaporama courant
}
