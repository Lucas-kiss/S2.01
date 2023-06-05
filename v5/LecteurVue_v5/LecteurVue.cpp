#include "LecteurVue.h"
#include "ui_LecteurVue.h"


#include<QApplication>
#include<QMessageBox>
#include<QInputDialog>



LecteurVue::LecteurVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LecteurVue)
{
    ui->setupUi(this);
    db=new Database();
    db->openDataBase();

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

    majLabel(vider);


    statusBar()->showMessage(tr("Mode Manuel"));
    ui->bArreterDiapo->setEnabled(false);
    ui->bLancerDiapo->setEnabled(false);
    afficher();



}

LecteurVue::~LecteurVue()
{
    delete ui;
}

void LecteurVue::LancerDiapo()
{
    statusBar()->showMessage(tr("Mode Automatique"));
    ui->bArreterDiapo->setEnabled(true);

    (*this)._posImageCourante=0;
    afficher();

    timer.setInterval(TPS);
    timer.start();
}

void LecteurVue::ArreterDiapo()
{
    statusBar()->showMessage(tr("Mode Manuel"));
    ui->bArreterDiapo->setEnabled(false);

    if(timer.isActive())
    {
        timer.stop();
    }

}

void LecteurVue::AllerAuSuivant()
{
    if(timer.isActive())
    {
        timer.stop();
        statusBar()->showMessage(tr("Mode Manuel"));
        ui->bArreterDiapo->setEnabled(false);
    }
    else{
        avancer();
        afficher();
    }
}

void LecteurVue::AllerAuPrecedent()
{
    if(timer.isActive())
    {
        timer.stop();
        statusBar()->showMessage(tr("Mode Manuel"));
        ui->bArreterDiapo->setEnabled(false);
    }
    else{
        reculer();
        afficher();
    }
}

void LecteurVue::SuivantAuto()
{
    timer.setInterval(TPS);
    avancer();
    afficher();
}

void LecteurVue::Quitter()
{
    this->close();
}

void LecteurVue::ChargerDiapo()
{
    chargerDiaporama();
    ui->bLancerDiapo->setEnabled(true);
    afficher();
}

void LecteurVue::EnleverDiapo()
{
    if(timer.isActive())
    {
        timer.stop();
        statusBar()->showMessage(tr("Mode Manuel"));
    }
    ui->bLancerDiapo->setEnabled(false);
    ui->bArreterDiapo->setEnabled(false);
    viderDiaporama();
}

void LecteurVue::ChangerVitesse()
{
    bool ok;
    double nombre = QInputDialog::getDouble(this, tr("Changer Vitesse"),
                                            tr("Vitesse en secondes :"),
                                            QLineEdit::Normal,
                                            0, 120, 1, &ok, Qt::WindowFlags(), 0.5);

    setVitesse(nombre*1000);
}

unsigned  int  LecteurVue::getVitesse(){
    return TPS;
}
void LecteurVue::setVitesse(unsigned int  v){
    TPS=v;

}
void LecteurVue::SeRenseigner()
{
    QMessageBox msgBox;
    msgBox.setText("Version: v4\nDate de Creation : 16/05/2023 \nAuteurs : KISS Lucas/DUBOS Lucie");
    msgBox.exec();
}

void LecteurVue::avancer()
{
    if ((*this)._posImageCourante==nbImages()-1)
    {
        (*this)._posImageCourante=0;
    }else{
        (*this)._posImageCourante=(*this)._posImageCourante+1;
    }

}

void LecteurVue::reculer()
{
    if ((*this)._posImageCourante==0)
    {
        (*this)._posImageCourante=nbImages()-1;
    }else{
        (*this)._posImageCourante=(*this)._posImageCourante-1;
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

    QSqlQuery query;

    query.exec("SELECT DiaposDansDiaporama.rang, Diapos.titrePhoto, Familles.nomFamille, Diapos.uriPhoto, Diaporamas.idDiaporama ,Diaporamas.vitesseDefilement,Diaporamas.`titre Diaporama` FROM Diaporamas JOIN DiaposDansDiaporama ON Diaporamas.idDiaporama=DiaposDansDiaporama.idDiaporama JOIN Diapos ON DiaposDansDiaporama.idDiapo=Diapos.idphoto JOIN Familles ON Diapos.idFam = Familles.idFamille WHERE Diaporamas.idDiaporama=2 ");

    query.next();
    setVitesse(query.value(5).toInt()*1000);
    nomDiapo=query.value(6).toString();
    query.previous();

    Image* imageACharger1;
    for(int i = 0; query.next(); i++){
    imageACharger1 = new Image(query.value(0).toUInt(), query.value(2).toString().toStdString(), query.value(1).toString().toStdString(), CHEMIN + query.value(3).toString().toStdString());
    _diaporama.push_back(imageACharger1);
    }

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

    (*this)._posImageCourante = 0;
    vider=true;

}

void LecteurVue::viderDiaporama()
{
    if (nbImages () > 0)
    {
        unsigned int taille = nbImages();
        for (unsigned int i = 0; i < taille ; i++)
        {
            _diaporama.pop_back(); /* Removes the last element in the vector,
                                      effectively reducing the container size by one.
                                      AND deletes the removed element */


        }
        vider=false;
        majLabel(vider);
        _posImageCourante = 0;
    }
    cout << nbImages() << " images restantes dans le diaporama." << endl;

}

void LecteurVue::majLabel(bool ok)
{
    if(ok){
        ui->lRang->setText((QString::number(_diaporama[_posImageCourante]->getRang())));
        ui->lNomRang->setText((tr("Rang : ")));
        ui->lImage->setPixmap(QPixmap(QString::fromStdString(_diaporama[_posImageCourante]->getChemin())));
        ui->lImage->setAlignment(Qt::AlignCenter);
        ui->lCategorie->setText(QString::fromStdString(_diaporama[_posImageCourante]->getCategorie()));
        ui->lNomCategorie->setText(tr("Categorie : "));
        ui->lTitre->setText((QString::fromStdString(_diaporama[_posImageCourante]->getTitre())));
        ui->lNomDiapo->setText(nomDiapo);
    }
    else{
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
    if(numDiaporamaCourant()>0){
        cout<<numDiaporamaCourant()<<endl<<nbImages()<<endl<<_posImageCourante<<endl;
        if (nbImages()!=0){
            majLabel(vider);
        }else
        {
            cout << "diaporama vide"<<endl;
        }
    }
    else
    {
        cout << "vide"<< endl;
    }

}

unsigned int LecteurVue::nbImages()
{
    return _diaporama.size();
}

Image *LecteurVue::imageCourante()
{
    return nullptr;
}

unsigned int LecteurVue::numDiaporamaCourant()
{
    return _numDiaporamaCourant;
}
