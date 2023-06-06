#ifndef LECTEURVUE_H
#define LECTEURVUE_H
#include "database.h"
#include <QMainWindow>
#include<QTimer>
#include  "diapo.h"

#define CHEMIN "F:/Documents/IUT/A1/S2.01/v6/LecteurVue_v6/ressources"

QT_BEGIN_NAMESPACE
namespace Ui { class LecteurVue; }
QT_END_NAMESPACE

class LecteurVue : public QMainWindow
{
    Q_OBJECT

public:
    LecteurVue(QWidget *parent = nullptr);
    ~LecteurVue();


private:
    Ui::LecteurVue *ui;
    Diaporama _diaporama;            // pointeurs vers les images du diaporama
    QTimer timer;
    unsigned int TPS = 2000;
    bool vider = false;
    Database *db;
    Diapo *diapo;

private:
    void chargerDiaporama();    // charge dans _diaporama les images du _numDiaporamaCourant
    void viderDiaporama();      // vide _diaporama de tous ses objets image et les delete
    void majLabel(bool);
    unsigned int getVitesse();          // retourne la vitesse à laquelle défile les diapositives
    void setVitesse(unsigned int);      // change la vitesse à laquelle défile les diapositives selon l'entier donné
    void avancer();             // incrémente _posImageCourante, modulo nbImages()
    void reculer();             // décrémente _posImageCourante, modulo nbImages()
    void changerDiaporama(unsigned int pNumDiaporama);    // permet de choisir un diaporama, 0 si aucun diaporama souhaité
    void afficher();            // affiche les informations sur lecteur-diaporama et image courante
    int choisirDiapo();

public slots:
    void LancerDiapo();
    void ArreterDiapo();
    void AllerAuSuivant();
    void AllerAuPrecedent();
    void SuivantAuto();
    void Quitter();
    void ChargerDiapo();
    void EnleverDiapo();
    void ChangerVitesse();
    void SeRenseigner();
   };
#endif // LECTEURVUE_H
