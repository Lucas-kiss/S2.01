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
    explicit choixDiapo(QWidget *parent = nullptr);    // Constructor
    ~choixDiapo();                                     // Destructor

    void afficher();                                    // Method for displaying the diaporamas
    QString getLigneSelect();                           // Method for getting the selected diaporama

private:
    Ui::choixDiapo *ui;                                 // Pointer to the UI object
    QString numDiapoSelect;                             // Selected diaporama number

private slots:
    void clicSurTable(int);                             // Slot for handling table cell clicks

};

#endif // CHOIXDIAPO_H
