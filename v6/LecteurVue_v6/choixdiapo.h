#ifndef CHOIXDIAPO_H
#define CHOIXDIAPO_H

#include <QDialog>

namespace Ui {
class choixDiapo;
}

class choixDiapo : public QDialog
{
    Q_OBJECT

public:
    explicit choixDiapo(QWidget *parent = nullptr); // Constructeur
    ~choixDiapo(); // Destructeur

    void afficher();                                    // Méthode pour afficher les diaporamas
    QString getLigneSelect();                           // Méthode pour obtenir le diaporama sélectionné
private:
    Ui::choixDiapo *ui; // Pointeur vers l'objet UI
    QString numDiapoSelect; // Numéro du diaporama sélectionné

private slots:
    void clicSurTable(int); // Slot pour gérer les clics sur les cellules de la table

};

#endif // CHOIXDIAPO_H
