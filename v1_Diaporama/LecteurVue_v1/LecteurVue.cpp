#include "LecteurVue.h" // Inclusion du fichier d'en-tête de la classe LecteurVue
#include "ui_LecteurVue.h" // Inclusion du fichier d'en-tête généré par l'outil de conception Qt

#include <QApplication> // Inclusion de la classe QApplication

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

    statusBar()->showMessage(tr("Mode Manuel")); // Affichage d'un message dans la barre de statut
}

LecteurVue::~LecteurVue()
{
    delete ui; // Suppression de l'interface utilisateur de la fenêtre
}

// Implémentation des slots

void LecteurVue::LancerDiapo()
{
    qDebug() << "Lancer diapo fonctionnel" << Qt::endl; // Affichage d'un message de débogage
}

void LecteurVue::ArreterDiapo()
{
    qDebug() << "Arreter Diapo fonctionnel" << Qt::endl; // Affichage d'un message de débogage
}

void LecteurVue::AllerAuSuivant()
{
    qDebug() << "Aller au suivant fonctionnel" << Qt::endl; // Affichage d'un message de débogage
}

void LecteurVue::AllerAuPrecedent()
{
    qDebug() << "Aller au precedent fonctionnel" << Qt::endl; // Affichage d'un message de débogage
}

void LecteurVue::Quitter()
{
    qDebug() << "Quitter fonctionnel" << Qt::endl; // Affichage d'un message de débogage
}

void LecteurVue::ChargerDiapo()
{
    qDebug() << "Charger la Diapo fonctionnel" << Qt::endl; // Affichage d'un message de débogage
}

void LecteurVue::EnleverDiapo()
{
    qDebug() << "Enlever la Diapo fonctionnel" << Qt::endl; // Affichage d'un message de débogage
}

void LecteurVue::ChangerVitesse()
{


    qDebug() << "Changer la Vitesse fonctionnel" << Qt::endl;   // Affichage d'un message de débogage
}

void LecteurVue::SeRenseigner()
{
    qDebug() << "Se Renseigner fonctionnel" << Qt::endl;    // Affichage d'un message de débogage
}
