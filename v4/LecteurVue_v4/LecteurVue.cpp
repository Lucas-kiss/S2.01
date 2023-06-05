#include "LecteurVue.h" // Inclusion du fichier d'en-tête de la classe LecteurVue
#include "ui_LecteurVue.h" // Inclusion du fichier d'en-tête généré par l'outil de conception Qt

#include <QApplication> // Inclusion de la classe QApplication
#include<QMessageBox>   // Inclusion de la classe QMessageBox
#include<QInputDialog>  // Inclusion de la classe QInputDialog

LecteurVue::LecteurVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LecteurVue)
{
    ui->setupUi(this); // Configuration de l'interface utilisateur de la fenêtre

    // Connexion des signaux (interactions de l'utilisateur) aux slots correspondants
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(SuivantAuto()));
    QObject::connect(ui->bLancerDiapo, SIGNAL(clicked()), this, SLOT(LancerDiapo()));
    QObject::connect(ui->bArreterDiapo, SIGNAL(clicked()), this, SLOT(ArreterDiapo()));
    QObject::connect(ui->bSuivant, SIGNAL(clicked()), this, SLOT(AllerAuSuivant()));
    QObject::connect(ui->bPrecedent, SIGNAL(clicked()), this, SLOT(AllerAuPrecedent()));
    QObject::connect(ui->actionQuitter, SIGNAL(clicked()), this, SLOT(Quitter()));
    QObject::connect(ui->actionCharger_diaporama, SIGNAL(clicked()), this, SLOT(ChargerDiapo()));
    QObject::connect(ui->actionEnlever_diaporama, SIGNAL(clicked()), this, SLOT(EnleverDiapo()));
    QObject::connect(ui->actionVitesse_de_defilement, SIGNAL(clicked()), this, SLOT(ChangerVitesse()));
    QObject::connect(ui->actionA_propos_de, SIGNAL(triggered()), this, SLOT(SeRenseigner()));

    majLabel(vider); // Appel d'une fonction majLabel() avec l'argument "vider"

    statusBar()->showMessage(tr("Mode Manuel")); // Affiche un message dans la barre de statut
    ui->bArreterDiapo->setEnabled(false); // Désactive le bouton "Arrêter Diapo"
    ui->bLancerDiapo->setEnabled(false); // Désactive le bouton "Lancer Diapo"
    afficher(); // Appel de la fonction afficher()
}

LecteurVue::~LecteurVue()
{
    delete ui; // Libère la mémoire utilisée par l'interface utilisateur
}

void LecteurVue::LancerDiapo()
{
    statusBar()->showMessage(tr("Mode Automatique")); // Affiche un message dans la barre de statut
    ui->bArreterDiapo->setEnabled(true); // Active le bouton "Arrêter Diapo"

    (*this)._posImageCourante = 0; // Définit la position de l'image courante à 0
    afficher(); // Appel de la fonction afficher()

    timer.setInterval(TPS); // Définit l'intervalle du timer avec la valeur de TPS
    timer.start(); // Démarre le timer
}


void LecteurVue::ArreterDiapo()
{
    statusBar()->showMessage(tr("Mode Manuel")); // Affiche un message dans la barre de statut
    ui->bArreterDiapo->setEnabled(false); // Désactive le bouton "Arrêter Diapo"

    if (timer.isActive())
    {
        timer.stop(); // Arrête le timer si celui-ci est actif
    }
}

void LecteurVue::AllerAuSuivant()
{
    if (timer.isActive())
    {
        timer.stop(); // Arrête le timer si celui-ci est actif
        statusBar()->showMessage(tr("Mode Manuel")); // Affiche un message dans la barre de statut
        ui->bArreterDiapo->setEnabled(false); // Désactive le bouton "Arrêter Diapo"
    }
    else
    {
        avancer(); // Appel de la fonction avancer() pour passer à l'image suivante
        afficher(); // Appel de la fonction afficher() pour afficher l'image courante
    }
}

void LecteurVue::AllerAuPrecedent()
{
    if (timer.isActive())
    {
        timer.stop(); // Arrête le timer si celui-ci est actif
        statusBar()->showMessage(tr("Mode Manuel")); // Affiche un message dans la barre de statut
        ui->bArreterDiapo->setEnabled(false); // Désactive le bouton "Arrêter Diapo"
    }
    else
    {
        reculer(); // Appel de la fonction reculer() pour revenir à l'image précédente
        afficher(); // Appel de la fonction afficher() pour afficher l'image courante
    }
}

void LecteurVue::SuivantAuto()
{
    timer.setInterval(TPS); // Définit l'intervalle du timer avec la valeur de TPS
    avancer(); // Appel de la fonction avancer() pour passer à l'image suivante
    afficher(); // Appel de la fonction afficher() pour afficher l'image courante
}

void LecteurVue::Quitter()
{
    this->close(); // Ferme la fenêtre de l'application
}

void LecteurVue::ChargerDiapo()
{
    chargerDiaporama(); // Appel de la fonction chargerDiaporama() pour charger le diaporama
    ui->bLancerDiapo->setEnabled(true); // Active le bouton "Lancer Diapo"
    afficher(); // Appel de la fonction afficher() pour afficher l'image courante
}

void LecteurVue::EnleverDiapo()
{
    if (timer.isActive())
    {
        timer.stop(); // Arrête le timer si celui-ci est actif
        statusBar()->showMessage(tr("Mode Manuel")); // Affiche un message dans la barre de statut
    }
    ui->bLancerDiapo->setEnabled(false); // Désactive le bouton "Lancer Diapo"
    ui->bArreterDiapo->setEnabled(false); // Désactive le bouton "Arrêter Diapo"
    viderDiaporama(); // Appel de la fonction viderDiaporama() pour vider le diaporama
}


void LecteurVue::ChangerVitesse()
{
    // Demande à l'utilisateur de saisir la nouvelle vitesse du diaporama
    bool ok;
    double nombre = QInputDialog::getDouble(this, tr("Changer Vitesse"),
                                            tr("Vitesse en secondes :"),
                                            QLineEdit::Normal,
                                            0, 120, 1, &ok, Qt::WindowFlags(), 0.5);

    // Met à jour la vitesse en convertissant la valeur saisie en millisecondes
    setVitesse(nombre * 1000);
}

unsigned int LecteurVue::getVitesse()
{
    // Retourne la valeur actuelle de la vitesse
    return TPS;
}

void LecteurVue::setVitesse(unsigned int v)
{
    // Modifie la vitesse du diaporama avec la nouvelle valeur fournie
    TPS = v;
}

void LecteurVue::SeRenseigner()
{
    // Affiche une boîte de dialogue avec des informations sur la version, la date de création et les auteurs du lecteur
    QMessageBox msgBox;
    msgBox.setText("Version: v4\nDate de Creation : 16/05/2023 \nAuteurs : KISS Lucas/DUBOS Lucie");
    msgBox.exec();
}

void LecteurVue::avancer()
{
    // Passe à l'image suivante dans le diaporama
    if ((*this)._posImageCourante == nbImages() - 1)
    {
        // Si la position de l'image courante est la dernière, revenir à la première position
        (*this)._posImageCourante = 0;
    }
    else
    {
        // Sinon, incrémenter la position de l'image courante de 1
        (*this)._posImageCourante = (*this)._posImageCourante + 1;
    }
}

void LecteurVue::reculer()
{
    if ((*this)._posImageCourante == 0)
    {
        // Si la position de l'image courante est la première, revenir à la dernière position
        (*this)._posImageCourante = nbImages() - 1;
    }
    else
    {
        // Sinon, décrémenter la position de l'image courante de 1
        (*this)._posImageCourante = (*this)._posImageCourante - 1;
    }
}

void LecteurVue::changerDiaporama(unsigned int pNumDiaporama)
{
    // Si un diaporama courant existe, le vider avant de charger le nouveau diaporama
    if (numDiaporamaCourant() > 0)
    {
        viderDiaporama();
    }

    // Met à jour le numéro du diaporama courant avec la valeur fournie
    _numDiaporamaCourant = pNumDiaporama;

    // Si un diaporama courant existe, charger le diaporama
    if (numDiaporamaCourant() > 0)
    {
        chargerDiaporama();
    }
}


void LecteurVue::chargerDiaporama()
{
    /* Chargement des images associées au diaporama courant
       Dans une version ultérieure, ces données proviendront d'une base de données,
       et correspondront au diaporama choisi */
    Image* imageACharger;
    imageACharger = new Image(3, "personne", "Blanche Neige", "F:/Documents/IUT/A1/S2.01/v3/LecteurVue_v3/ressources/cartesDisney/carteDisney2.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(2, "personne", "Cendrillon", "F:/Documents/IUT/A1/S2.01/v3/LecteurVue_v3/ressources/cartesDisney/carteDisney4.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(4, "animal", "Mickey", "F:/Documents/IUT/A1/S2.01/v3/LecteurVue_v3/ressources/cartesDisney/carteDisney1.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(1, "personne", "Grincheux", "F:/Documents/IUT/A1/S2.01/v3/LecteurVue_v3/ressources/cartesDisney/carteDisney1.gif");
    _diaporama.push_back(imageACharger);

    // Trier les images en fonction du rang
    Image* copy;
    for (unsigned int ici = nbImages(); ici > 1; ici--) {
        for (unsigned int i = 0; i < ici-1 ; ++i) {
            if((*this)._diaporama[i]->getRang()>(*this)._diaporama[i+1]->getRang())
            {
                copy = (*this)._diaporama.at(i);
                (*this)._diaporama.at(i)=(*this)._diaporama.at(i+1);
                (*this)._diaporama.at(i+1)=copy;
            }
        }
    }



    (*this)._posImageCourante = 0; // initialiser la position de l'image courante à 0

    vider=true;


}

void LecteurVue::viderDiaporama()
{
    if (nbImages () > 0) // Vérifie s'il y a des images dans le diaporama
    {
        unsigned int taille = nbImages(); // Stocke le nombre d'images dans une variable
        for (unsigned int i = 0; i < taille ; i++) // Parcourt toutes les images du diaporama
        {
            _diaporama.pop_back(); // Supprime le dernier élément du vecteur (image)
            // Cela réduit efficacement la taille du conteneur d'un élément

        }

        vider = false; // Met à jour la variable vider à false
        majLabel(vider); // Met à jour l'étiquette associée dans l'interface utilisateur
        _posImageCourante = 0; // Réinitialise la position de l'image courante à zéro
    }

    cout << nbImages() << " images restantes dans le diaporama." << endl;
}


void LecteurVue::majLabel(bool ok)
{
    if (ok) // Si ok est vrai
    {
        // Met à jour les étiquettes avec les valeurs de l'image courante dans le diaporama
        ui->lRang->setText((QString::number(_diaporama[_posImageCourante]->getRang())));
        ui->lNomRang->setText((tr("Rang : ")));
        ui->lImage->setPixmap(QPixmap(QString::fromStdString(_diaporama[_posImageCourante]->getChemin())));
        ui->lImage->setAlignment(Qt::AlignCenter);
        ui->lCategorie->setText(QString::fromStdString(_diaporama[_posImageCourante]->getCategorie()));
        ui->lNomCategorie->setText(tr("Categorie : "));
        ui->lTitre->setText((QString::fromStdString(_diaporama[_posImageCourante]->getTitre())));
        ui->lNomDiapo->setText((tr("Nom Diaporama")));
    }
    else // Si ok est faux
    {
        // Réinitialise les étiquettes en tant que chaînes vides
        ui->lRang->setText((tr("")));
        ui->lNomRang->setText((tr("")));
        ui->lImage->setPixmap(QPixmap(tr("")));
        ui->lCategorie->setText(tr(""));
        ui->lNomCategorie->setText(tr(""));
        ui->lTitre->setText(tr(""));
        ui->lNomDiapo->setText((tr("")));
    }
}

void LecteurVue::afficher()
{
    if (numDiaporamaCourant() > 0) // Vérifie s'il y a un diaporama courant
    {
        cout << numDiaporamaCourant() << endl << nbImages() << endl << _posImageCourante << endl;

        if (nbImages() != 0) // Vérifie s'il y a des images dans le diaporama
        {
            majLabel(vider); // Met à jour les étiquettes dans l'interface utilisateur
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
    return _diaporama.size(); // Renvoie le nombre d'images dans le diaporama
}


Image *LecteurVue::imageCourante()
{
    return nullptr; // Renvoie un pointeur nul car la fonction n'est pas implémentée
}


unsigned int LecteurVue::numDiaporamaCourant()
{
    return _numDiaporamaCourant; // Renvoie le numéro du diaporama courant
}

