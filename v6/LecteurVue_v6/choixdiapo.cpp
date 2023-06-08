#include "choixdiapo.h" // Inclusion du fichier d'en-tête de la classe choixDiapo
#include "QSqlQuery" // Inclusion de la classe QSqlQuery
#include "ui_choixdiapo.h" // Inclusion de la classe Ui::choixDiapo

choixDiapo::choixDiapo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::choixDiapo)
{
    ui->setupUi(this);

    connect(ui->tableWidget, SIGNAL(cellClicked(int, int)), this, SLOT(clicSurTable(int)));

    afficher(); // Appelle la méthode afficher() pour afficher les données dans le tableau
}

choixDiapo::~choixDiapo()
{
    delete ui; // Supprime l'interface utilisateur choixDiapo
}

void choixDiapo::clicSurTable(int row)
{
    QTableWidgetItem *item = ui->tableWidget->item(row, 0); // Obtient l'élément dans la colonne 0 de la ligne cliquée
    if (item != nullptr) {
        QString text = item->text(); // Récupère le texte de l'élément
        numDiapoSelect = text; // Stocke le numéro de diaporama sélectionné
    }
}

void choixDiapo::afficher()
{
    QSqlQuery query;
    query.exec("SELECT idDiaporama, `titre Diaporama` FROM Diaporamas;"); // Exécute la requête SQL pour récupérer les données des diaporamas

    for (int i = 0; query.next(); i++) {
        qDebug() << query.value(0) << query.value(1) << Qt::endl; // Affiche les valeurs récupérées dans la console
        ui->tableWidget->insertRow(i); // Insère une nouvelle ligne dans le tableau
        QTableWidgetItem *idDiapo = new QTableWidgetItem(query.value(0).toString()); // Crée un nouvel élément pour l'ID du diaporama
        QTableWidgetItem *titreDiapo = new QTableWidgetItem(query.value(1).toString()); // Crée un nouvel élément pour le titre du diaporama
        ui->tableWidget->setItem(i, 0, idDiapo); // Ajoute l'élément de l'ID du diaporama à la colonne 0 de la ligne i
        ui->tableWidget->setItem(i, 1, titreDiapo); // Ajoute l'élément du titre du diaporama à la colonne 1 de la ligne i
    }

    QHeaderView *headerView = ui->tableWidget->horizontalHeader(); // Obtient l'en-tête horizontal du tableau
    headerView->setSectionResizeMode(QHeaderView::Stretch); // Définit le mode de redimensionnement des sections pour qu'elles s'étirent pour remplir l'espace disponible
}

QString choixDiapo::getLigneSelect()
{
    return numDiapoSelect; // Retourne le numéro de diaporama sélectionné
}

