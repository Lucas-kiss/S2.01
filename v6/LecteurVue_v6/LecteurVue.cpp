#include "LecteurVue.h"
#include "ui_LecteurVue.h"

#include<QApplication>
#include<QMessageBox>
#include<QInputDialog>
#include<QListWidget>
#include <QDebug>



LecteurVue::LecteurVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LecteurVue)
{
    ui->setupUi(this); // Initialise l'interface utilisateur
    db=new Database(); // Initialise la base de données
    db->openDataBase(); // Ouvre la base de données
    diapo= new Diapo(); // Initialise l'objet diaporama

    // Connexion des signaux et des slots
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

    majLabel(vider); // Met à jour l'affichage

    statusBar()->showMessage(tr("Mode Manuel")); // Affiche un message dans la barre de statut
    ui->bArreterDiapo->setEnabled(false); // Désactive le bouton d'arrêt du diaporama
    ui->bLancerDiapo->setEnabled(false); // Désactive le bouton de lancement du diaporama
    afficher(); // Affiche le diaporama



}

LecteurVue::~LecteurVue()
{
    delete ui; // Supprime l'interface utilisateur
}

void LecteurVue::LancerDiapo()
{
    statusBar()->showMessage(tr("Mode Automatique")); // Affiche un message dans la barre de statut
    ui->bArreterDiapo->setEnabled(true); // Active le bouton d'arrêt du diaporama

    diapo->setPosCourante(0); // Réinitialise la position courante du diaporama
    afficher(); // Affiche le diaporama

    timer.setInterval(TPS); // Définit l'intervalle du timer
    timer.start(); // Démarre le timer
}


void LecteurVue::ArreterDiapo()
{
    statusBar()->showMessage(tr("Mode Manuel")); // Affiche un message dans la barre de statut
    ui->bArreterDiapo->setEnabled(false); // Désactive le bouton d'arrêt du diaporama

    if(timer.isActive()) // Vérifie si le timer est actif
    {
        timer.stop(); // Arrête le timer
    }
}

void LecteurVue::AllerAuSuivant()
{
    if(timer.isActive()) // Vérifie si le timer est actif
    {
        timer.stop(); // Arrête le timer
        statusBar()->showMessage(tr("Mode Manuel")); // Affiche un message dans la barre de statut
        ui->bArreterDiapo->setEnabled(false); // Désactive le bouton d'arrêt du diaporama
    }
    else
    {
        avancer(); // Passe à l'image suivante
        afficher(); // Affiche le diaporama
    }
}

void LecteurVue::AllerAuPrecedent()
{
    if(timer.isActive()) // Vérifie si le timer est actif
    {
        timer.stop(); // Arrête le timer
        statusBar()->showMessage(tr("Mode Manuel")); // Affiche un message dans la barre de statut
        ui->bArreterDiapo->setEnabled(false); // Désactive le bouton d'arrêt du diaporama
    }
    else
    {
        reculer(); // Passe à l'image précédente
        afficher(); // Affiche le diaporama
    }
}

void LecteurVue::SuivantAuto()
{
    timer.setInterval(TPS); // Définit l'intervalle du timer
    avancer(); // Passe à l'image suivante
    afficher(); // Affiche le diaporama
}

void LecteurVue::Quitter()
{
    this->close(); // Ferme la fenêtre principale
}

void LecteurVue::ChargerDiapo()
{
    chargerDiaporama(); // Charger un diaporama à partir de la base de données ou d'un fichier
    ui->bLancerDiapo->setEnabled(true); // Activer le bouton pour lancer le diaporama
    afficher(); // Afficher le diaporama sur l'interface utilisateur
}


void LecteurVue::EnleverDiapo()
{
    if(timer.isActive()) // Vérifier si le timer du diaporama est actif
    {
        timer.stop(); // Arrêter le timer
        statusBar()->showMessage(tr("Mode Manuel")); // Afficher le message "Mode Manuel" dans la barre de statut
    }
    ui->bLancerDiapo->setEnabled(false); // Désactiver le bouton pour lancer le diaporama
    ui->bArreterDiapo->setEnabled(false); // Désactiver le bouton pour arrêter le diaporama
    viderDiaporama(); // Vider le diaporama
}

void LecteurVue::ChangerVitesse()
{
    bool ok;
    double nombre = QInputDialog::getDouble(this, tr("Changer Vitesse"),
                                            tr("Vitesse en secondes :"),
                                            QLineEdit::Normal,
                                            0, 120, 1, &ok, Qt::WindowFlags(), 0.5);

    setVitesse(nombre*1000); // Modifier la vitesse en multipliant le nombre par 1000
}


unsigned int LecteurVue::getVitesse()
{
    return TPS; // Retourner la valeur de la vitesse
}

void LecteurVue::setVitesse(unsigned int v)
{
    TPS = v; // Modifier la valeur de la vitesse
}

void LecteurVue::SeRenseigner()
{
    QMessageBox msgBox;
    msgBox.setText("Version: v4\nDate de Creation : 16/05/2023 \nAuteurs : KISS Lucas/DUBOS Lucie");
    msgBox.exec();
}

void LecteurVue::avancer()
{
    if (diapo->getPosCourante() == diapo->getNbImages() - 1)
    {
        diapo->setPosCourante(0); // Si la position courante est la dernière image, revenir à la première image
    }
    else
    {
        diapo->setPosCourante(diapo->getPosCourante() + 1); // Avancer à la prochaine image
    }
}


void LecteurVue::reculer()
{
    if (diapo->getPosCourante() == 0)
    {
        diapo->setPosCourante(diapo->getNbImages() - 1); // Si la position courante est la première image, revenir à la dernière image
    }
    else
    {
        diapo->setPosCourante(diapo->getPosCourante() - 1); // Reculer vers l'image précédente
    }
}


void LecteurVue::changerDiaporama(unsigned int pNumDiaporama)
{
    // s'il y a un diaporama courant, le vider, puis charger le nouveau Diaporama
    if (diapo->getId() > 0)
    {
        viderDiaporama(); // Vider le diaporama courant s'il en existe un
    }
    diapo->setId(pNumDiaporama); // Définir l'ID du nouveau diaporama
    if (diapo->getId() == 0)
    {
        chargerDiaporama(); // charge le diaporama courant
    }

}

void LecteurVue::chargerDiaporama()
{
    /* Chargement des images associées au diaporama courant
       Dans une version ultérieure, ces données proviendront d'une base de données,
       et correspondront au diaporama choisi */

    // Affichage de la fenêtre de choix du diaporama
    choixDiapo *maDlg = new choixDiapo(this);
    maDlg->exec();

    // Préparation de la requête SQL pour récupérer les informations du diaporama sélectionné
    QSqlQuery query;
    query.prepare("SELECT DiaposDansDiaporama.rang, Diapos.titrePhoto, Familles.nomFamille, Diapos.uriPhoto, Diaporamas.idDiaporama ,Diaporamas.vitesseDefilement,Diaporamas.`titre Diaporama` FROM Diaporamas JOIN DiaposDansDiaporama ON Diaporamas.idDiaporama=DiaposDansDiaporama.idDiaporama JOIN Diapos ON DiaposDansDiaporama.idDiapo=Diapos.idphoto JOIN Familles ON Diapos.idFam = Familles.idFamille WHERE Diaporamas.idDiaporama=?");
    query.addBindValue(maDlg->getLigneSelect());
    query.exec();
    query.next();

    // Mise à jour des informations du diaporama avec les valeurs récupérées de la base de données
    diapo->setId(query.value(4).toUInt());
    diapo->setNom(query.value(6).toString().toStdString());
    diapo->setVitesse(query.value(5).toUInt() * 1000);
    setVitesse(diapo->getVitesse());

    unsigned int nbrImage = 0;
    Image* imageACharger1;

    // Boucle pour charger les images associées au diaporama
    for (int i = 0; query.next(); i++)
    {
        // Création d'une nouvelle instance de la classe Image avec les valeurs récupérées de la base de données
        imageACharger1 = new Image(query.value(0).toInt(), query.value(2).toString().toStdString(), query.value(1).toString().toStdString(), CHEMIN + query.value(3).toString().toStdString());

        // Ajout de l'image à la liste du diaporama
        _diaporama.push_back(imageACharger1);
        nbrImage += 1;
    }

    // Mise à jour du nombre total d'images dans le diaporama
    diapo->setNbImages(nbrImage);

    Image* copy;

    // Tri des images dans l'ordre croissant des rangs
    for (unsigned int ici = diapo->getNbImages(); ici > 1; ici--)
    {
        for (unsigned int i = 0; i < ici - 1; ++i)
        {
            if (_diaporama[i]->getRang() > _diaporama[i + 1]->getRang())
            {
                // Échange des positions des images si elles ne sont pas dans l'ordre
                copy = _diaporama.at(i);
                _diaporama.at(i) = _diaporama.at(i + 1);
                _diaporama.at(i + 1) = copy;
            }
        }
    }

    // Réinitialisation de la position courante du diaporama à la première image
    diapo->setPosCourante(0);

    // Indicateur pour indiquer que le diaporama est vidé (pour être rechargé)
    vider = true;
}



void LecteurVue::viderDiaporama()
{
    if (diapo->getNbImages() > 0)
    {
        // Récupération de la taille actuelle du diaporama
        unsigned int taille = diapo->getNbImages();

        // Boucle pour supprimer les images du diaporama
        for (unsigned int i = 0; i < taille; i++)
        {
            _diaporama.pop_back(); // Supprime le dernier élément du vecteur et libère la mémoire de l'élément supprimé
        }

        // Réinitialisation de l'indicateur vider
        vider = false;

        // Mise à jour de l'affichage du label
        majLabel(vider);

        // Réinitialisation de la position courante du diaporama à la première image
        diapo->setPosCourante(0);
    }

    // Affichage du nombre d'images restantes dans le diaporama
    cout << diapo->getNbImages() << " images restantes dans le diaporama." << endl;
}


void LecteurVue::majLabel(bool ok)
{
    if(ok){
        // Mise à jour des labels avec les informations de l'image courante
        ui->lRang->setText((QString::number(_diaporama[diapo->getPosCourante()]->getRang())));
        ui->lNomRang->setText((tr("Rang : ")));
        ui->lImage->setPixmap(QPixmap(QString::fromStdString(_diaporama[diapo->getPosCourante()]->getChemin())));
        ui->lImage->setAlignment(Qt::AlignCenter);
        ui->lCategorie->setText(QString::fromStdString(_diaporama[diapo->getPosCourante()]->getCategorie()));
        ui->lNomCategorie->setText(tr("Categorie : "));
        ui->lTitre->setText((QString::fromStdString(_diaporama[diapo->getPosCourante()]->getTitre())));
        ui->lNomDiapo->setText(QString::fromStdString(diapo->getNom()));
    }
    else{
        // Réinitialisation des labels
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
    if (diapo->getId() > 0)
    {
        // Affichage de l'identifiant du diaporama, le nombre d'images et la position courante
        cout << diapo->getId() << endl << diapo->getNbImages() << endl << diapo->getPosCourante() << endl;

        if (diapo->getPosCourante() != 0)
        {
            majLabel(vider); // Met à jour les étiquettes dans l'interface utilisateur si la position courante n'est pas à zéro
        }

        if (diapo->getNbImages() != 0)
        {
            majLabel(vider); // Met à jour les étiquettes dans l'interface utilisateur s'il y a des images dans le diaporama
        }
        else
        {
            cout << "diaporama vide" << endl; // Affiche un message indiquant que le diaporama est vide
        }
    }
    else
    {
        cout << "vide" << endl; // Affiche un message indiquant que le diaporama est vide
    }
}
