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
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(SuivantAuto()));
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
    imageACharger = new Image(1, "personne", "Blanche Neige", "..\\LecteurVue_v3\\ressources\\cartesDisney\\disney_19.gif");
    _diaporama.push_back(imageACharger);

    // Création et ajout de l'image "Cendrillon" au diaporama
    imageACharger = new Image(2, "personne","Cendrillon", "..\\LecteurVue_v3\\ressources\\cartesDisney\\Disney_4.gif");
    _diaporama.push_back(imageACharger);

    // Création et ajout de l'image "Mickey" au diaporama
    imageACharger = new Image(3, "animal", "Mickey", "..\\LecteurVue_v3\\ressources\\cartesDisney\\disney_1.gif");
    _diaporama.push_back(imageACharger);

    // Création et ajout de l'image "Grincheux" au diaporama
    imageACharger = new Image(4, "personne", "Grincheux", "..\\LecteurVue_v3\\ressources\\cartesDisney\\disney_2.gif");
    _diaporama.push_back(imageACharger);


    statusBar()->showMessage(tr("Mode Manuel")); // Affichage d'un message dans la barre de statut

    ui->bArreterDiapo->setEnabled(false);   // Rend le bouton pour arrêter le mode auto du diapo non disponible
    (*this)._posImageCourante = 2;      // Initialise la position courante de l'image à 1
    _numDiaporamaCourant = 1;   // Initialise numéro du diaporama courant à 1
    afficher();

}

/* Destructeur de la classe LecteurVue */
LecteurVue::~LecteurVue()
{
    delete ui;
}

/* Méthode pour lancer le diaporama en mode automatique */
void LecteurVue::LancerDiapo()
{
    statusBar()->showMessage(tr("Mode Automatique"));
    ui->bArreterDiapo->setEnabled(true);
    (*this)._posImageCourante = 0;
    afficher();

    timer.setInterval(TPS); // Définit l'intervalle de temps entre chaque image
    timer.start(); // Démarre le timer pour avancer automatiquement les images
}

/* Méthode pour arrêter le diaporama */
void LecteurVue::ArreterDiapo()
{
    statusBar()->showMessage(tr("Mode Manuel"));
    ui->bArreterDiapo->setEnabled(false);

    if (timer.isActive())
    {
        timer.stop(); // Arrête le timer
    }


}

/* Méthode pour passer à l'image suivante dans le diaporama */
void LecteurVue::AllerAuSuivant()
{
    if (timer.isActive()) // Si le diaporama est en mode automatique, l'arrête en passant au mode manuel
    {
        timer.stop();
        statusBar()->showMessage(tr("Mode Manuel"));
        ui->bArreterDiapo->setEnabled(false);
    }
    else
    {
        avancer(); // Passe à l'image suivante
        afficher(); // Affiche l'image courante
    }
}

/* Méthode pour revenir à l'image précédente dans le diaporama */
void LecteurVue::AllerAuPrecedent()
{
    if (timer.isActive()) // Si le diaporama est en mode automatique, l'arrête en passant au mode manuel
    {
        timer.stop();
        statusBar()->showMessage(tr("Mode Manuel"));
        ui->bArreterDiapo->setEnabled(false);
    }
    else
    {
        reculer(); // Passe à l'image précédente
        afficher(); // Affiche l'image courante
    }
}

/* Méthode pour passer automatiquement à l'image suivante dans le diaporama */
void LecteurVue::SuivantAuto()
{
    avancer(); // Passe à l'image suivante
    afficher(); // Affiche l'image courante
}

/* Méthode pour quitter l'application */
void LecteurVue::Quitter()
{
    this->close(); // Ferme la fenêtre de l'application
}

/* Méthode pour charger un diaporama */
void LecteurVue::ChargerDiapo()
{
    qDebug() << "Charger la Diapo fonctionnel" << Qt::endl; // Affiche un message de débogage
}

/* Méthode pour enlever un diaporama */
void LecteurVue::EnleverDiapo()
{
    qDebug() << "Enlever la Diapo fonctionnel" << Qt::endl; // Affiche un message de débogage
}

/* Méthode pour changer la vitesse du diaporama */
void LecteurVue::ChangerVitesse()
{
    qDebug() << "Changer la Vitesse fonctionnel" << Qt::endl; // Affiche un message de débogage
}

/* Méthode pour afficher les informations sur l'application */
void LecteurVue::SeRenseigner()
{
    QMessageBox msgBox;
    msgBox.setText("Version: v3\nDate de Creation : 10/05/2023 \nAuteurs : KISS Lucas/DUBOS Lucie");
    msgBox.exec(); // Affiche une boîte de dialogue avec les informations sur l'application
}

/* Méthode pour avancer à l'image suivante dans le diaporama */
void LecteurVue::avancer()
{
    if ((*this)._posImageCourante == nbImages() - 1) // Si on est à la dernière image, retourne à la première image
    {
        (*this)._posImageCourante = 0;
    }
    else
    {
        (*this)._posImageCourante = (*this)._posImageCourante + 1; // Passe à l'image suivante
    }
}

/* Méthode pour reculer à l'image précédente dans le diaporama */
void LecteurVue::reculer()
{
    if ((*this)._posImageCourante == 0) // Si on est à la première image, passe à la dernière image
    {
        (*this)._posImageCourante = nbImages() - 1;
    }
    else
    {
        (*this)._posImageCourante = (*this)._posImageCourante - 1; // Passe à l'image précédente
    }
}

void LecteurVue::changerDiaporama(unsigned int pNumDiaporama)
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


void LecteurVue::chargerDiaporama()
{
    /* Chargement des images associées au diaporama courant
       Dans une version ultérieure, ces données proviendront d'une base de données,
       et correspondront au diaporama choisi */
    Image* imageACharger;
    imageACharger = new Image(3, "personne", "Blanche Neige", "..\\LecteurVue_v3\\ressources\\cartesDisney\\carteDisney2.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(2, "personne", "Cendrillon", "..\\LecteurVue_v3\\ressources\\cartesDisney\\carteDisney4.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(4, "animal", "Mickey", "..\\LecteurVue_v3\\ressources\\cartesDisney\\carteDisney1.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(1, "personne", "Grincheux", "..\\LecteurVue_v3\\ressources\\cartesDisney\\carteDisney1.gif");
    _diaporama.push_back(imageACharger);

    // Trier les images en fonction du rang
    Image* copy;
    for (unsigned int ici = nbImages(); ici > 1; ici--) {
        for (unsigned int i = 0; i < ici-1 ; ++i) {
            if (_diaporama[i]->getRang() > _diaporama[i+1]->getRang())
            {
                copy = _diaporama[i];
                _diaporama[i] = _diaporama[i+1];
                _diaporama[i+1] = copy;
            }
        }
    }

    _posImageCourante = 0; // initialiser la position de l'image courante à 0

    cout << "Diaporama num. " << numDiaporamaCourant() << " sélectionné." << endl;
    cout << nbImages() << " images chargées dans le diaporama" << endl;
}


void LecteurVue::viderDiaporama()
{
    if (nbImages() > 0)
    {
        unsigned int taille = nbImages();
        for (unsigned int i = 0; i < taille; i++)
        {
            _diaporama.pop_back(); /* Supprime le dernier élément du vecteur,
                                      réduisant ainsi la taille du conteneur d'une unité. */
        }
        _posImageCourante = 0;
    }
    cout << nbImages() << " images restantes dans le diaporama." << endl;
}


void LecteurVue::afficher()
{
    if (numDiaporamaCourant() > 0) // Vérifie si un diaporama courant existe
    {
        cout << endl << numDiaporamaCourant() << endl << nbImages() << endl << _posImageCourante << endl; // Affiche des informations sur le diaporama courant
        if (nbImages() != 0) // Vérifie si le diaporama contient des images
        {
            // Met à jour les attributs de l'interface utilisateur avec les valeurs de l'image courante
            ui->lRang->setText((QString::number(_diaporama[_posImageCourante]->getRang())));
            ui->lImage->setPixmap(QPixmap(QString::fromStdString(_diaporama[_posImageCourante]->getChemin())));
            ui->lImage->setAlignment(Qt::AlignCenter);
            ui->lCategorie->setText(QString::fromStdString(_diaporama[_posImageCourante]->getCategorie()));
            ui->lTitre->setText((QString::fromStdString(_diaporama[_posImageCourante]->getTitre())));
        }
        else
        {
            cout << "diaporama vide" << endl; // Affiche un message si le diaporama est vide
        }
    }
    else
    {
        cout << "vide" << endl; // Affiche un message si aucun diaporama n'est sélectionné
    }
}

unsigned int LecteurVue::nbImages()
{
    return _diaporama.size(); // Renvoie le nombre d'images dans le diaporama
}

Image* LecteurVue::imageCourante()
{
    return nullptr; // Renvoie un pointeur nul (pas implémenté)
}

unsigned int LecteurVue::numDiaporamaCourant()
{
    return _numDiaporamaCourant; // Renvoie le numéro du diaporama courant
}
