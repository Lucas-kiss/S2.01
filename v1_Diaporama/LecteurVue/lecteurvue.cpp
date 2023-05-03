#include "LecteurVue.h"
#include "ui_LecteurVue.h"

#include<QApplication>

LecteurVue::LecteurVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LecteurVue)
{
    ui->setupUi(this);

    QObject::connect( ui->bLancerDiapo, SIGNAL(clicked()), this, SLOT(LancerDiapo()) );
    QObject::connect( ui->bArreterDiapo, SIGNAL(clicked()), this, SLOT(ArreterDiapo()) );
    QObject::connect( ui->bSuivant, SIGNAL(clicked()), this, SLOT(AllerAuSuivant()) );
    QObject::connect( ui->bPrecedent, SIGNAL(clicked()), this, SLOT(AllerAuPrecedent()) );
    QObject::connect( ui->actionQuitter, SIGNAL(clicked()), this, SLOT(Quitter()) );
    QObject::connect( ui->actionCharger_diaporama, SIGNAL(clicked()), this, SLOT(ChargerDiapo()) );
    QObject::connect( ui->actionEnlever_diaporama, SIGNAL(clicked()), this, SLOT(EnleverDiapo()) );
    QObject::connect( ui->actionVitesse_de_defilement, SIGNAL(clicked()), this, SLOT(ChangerVitesse()) );
    QObject::connect( ui->actionA_propos_de, SIGNAL(triggered()), this, SLOT(SeRenseigner()) );

}

LecteurVue::~LecteurVue()
{
    delete ui;
}

void LecteurVue::LancerDiapo()
{
    qDebug() << "Lancer diapo fonctionnel" << Qt::endl;
}

void LecteurVue::ArreterDiapo()
{
    qDebug() << "Arreter Diapo fonctionnel" << Qt::endl;
}

void LecteurVue::AllerAuSuivant()
{
    qDebug() << "Aller au suivant fonctionnel" << Qt::endl;
}

void LecteurVue::AllerAuPrecedent()
{
    qDebug() << "Aller au precedent fonctionnel" << Qt::endl;
}

void LecteurVue::Quitter()
{
    qDebug() << "Quitter fonctionnel" << Qt::endl;
}

void LecteurVue::ChargerDiapo()
{
    qDebug() << "Charger la Diapo fonctionnel" << Qt::endl;
}

void LecteurVue::EnleverDiapo()
{
    qDebug() << "Enlever la Diapo fonctionnel" << Qt::endl;
}

void LecteurVue::ChangerVitesse()
{
    qDebug() << "Changer la Vitesse fonctionnel" << Qt::endl;
}

void LecteurVue::SeRenseigner()
{
    qDebug() << "Se Renseigner fonctionnel" << Qt::endl;
}
