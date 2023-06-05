#ifndef LECTEURVUE_H
#define LECTEURVUE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class LecteurVue; }
QT_END_NAMESPACE

class LecteurVue : public QMainWindow
{
    Q_OBJECT

public:
    LecteurVue(QWidget *parent = nullptr); // Constructeur de la classe
    ~LecteurVue(); // Destructeur de la classe

private:
    Ui::LecteurVue *ui; // Pointeur vers l'interface utilisateur de la classe

public slots:
    void LancerDiapo(); // Slot pour lancer le diaporama en mode automatique
    void ArreterDiapo(); // Slot pour arrêter le mode automatique du diaporama et passer en mode manuel
    void AllerAuSuivant(); // Slot pour passer à l'image suivante dans le diaporama
    void AllerAuPrecedent(); // Slot pour passer à l'image précédente dans le diaporama
    void Quitter(); // Slot pour quitter l'application
    void ChargerDiapo(); // Slot pour charger un diaporama
    void EnleverDiapo(); // Slot pour enlever un diaporama
    void ChangerVitesse(); // Slot pour changer la vitesse du diaporama
    void SeRenseigner(); // Slot pour obtenir des informations supplémentaires
};
#endif // LECTEURVUE_H

