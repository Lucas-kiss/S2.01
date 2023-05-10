#include "LecteurVue.h"
#include "ui_LecteurVue.h"


#include<QApplication>
#include<QMessageBox>


LecteurVue::LecteurVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LecteurVue)
{
    ui->setupUi(this);
    QObject::connect( ui->bLancerDiapo, SIGNAL(clicked()), this, SLOT(LancerDiapo()) );
    QObject::connect( ui->bArreterDiapo, SIGNAL(clicked()), this, SLOT(ArreterDiapo()) );
    QObject::connect( ui->bSuivant, SIGNAL(clicked()), this, SLOT(AllerAuSuivant()) );
    QObject::connect( ui->bPrecedent, SIGNAL(clicked()), this, SLOT(AllerAuPrecedent()) );
    QObject::connect( ui->actionQuitter, SIGNAL(triggered()), this, SLOT(Quitter()) );
    QObject::connect( ui->actionCharger_diaporama, SIGNAL(triggered()), this, SLOT(ChargerDiapo()) );
    QObject::connect( ui->actionEnlever_diaporama, SIGNAL(triggered()), this, SLOT(EnleverDiapo()) );
    QObject::connect( ui->actionVitesse_de_defilement, SIGNAL(triggered()), this, SLOT(ChangerVitesse()) );
    QObject::connect( ui->actionA_propos_de, SIGNAL(triggered()), this, SLOT(SeRenseigner()) );

    Image* imageACharger;
       imageACharger = new Image(1, "personne", "Blanche Neige", "F:/Documents/IUT/A1/S2.01/v2/LecteurVue/ressources/cartesDisney/disney_19.gif");
       _diaporama.push_back(imageACharger);
       imageACharger = new Image(2, "personne", "Cendrillon", "F:/Documents/IUT/A1/S2.01/v2/LecteurVue/ressources/cartesDisney/Disney_0.png");
       _diaporama.push_back(imageACharger);
       imageACharger = new Image(3, "animal", "Mickey", "F:/Documents/IUT/A1/S2.01/v2/LecteurVue/ressources/cartesDisney/disney_1.gif");
       _diaporama.push_back(imageACharger);
       imageACharger = new Image(4, "personne", "Grincheux", "F:/Documents/IUT/A1/S2.01/v2/LecteurVue/ressources/cartesDisney/disney_2.gif");
       _diaporama.push_back(imageACharger);

        statusBar()->showMessage(tr("Mode Manuel"));


       (*this)._posImageCourante = 0;
       _numDiaporamaCourant = 1;
       afficher();
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
    avancer();
    afficher();
}

void LecteurVue::AllerAuPrecedent()
{
    reculer();
    afficher();
}

void LecteurVue::Quitter()
{
    this->hide();
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
    QMessageBox msgBox;
    msgBox.setText("Version: v2 /nDate de Creation : 03/05/2023 /nAuteurs : KISS Lucas/DUBOS Lucie");
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
    Image* imageACharger;
    imageACharger = new Image(3, "personne", "Blanche Neige", "C://cartesDisney//carteDisney2.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(2, "personne", "Cendrillon", "C://cartesDisney//carteDisney4.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(4, "animal", "Mickey", "C://cartesDisney//carteDisney1.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(1, "personne", "Grincheux", "C://cartesDisney//carteDisney1.gif");
    _diaporama.push_back(imageACharger);

    Image* copy;
    for (unsigned int ici = nbImages(); ici > 1; ici--) {
        for (unsigned int i = 0; i < ici-1 ; ++i) {
            if((*this)._diaporama[i]->getRang()>(*this)._diaporama[i+1]->getRang())
            {
                cout<<"test"<<endl;
                copy = (*this)._diaporama.at(i);
                (*this)._diaporama.at(i)=(*this)._diaporama.at(i+1);
                (*this)._diaporama.at(i+1)=copy;
            }
        }
    }



     (*this)._posImageCourante = 0;

     cout << "Diaporama num. " << numDiaporamaCourant() << " selectionne. " << endl;
     cout << nbImages() << " images chargees dans le diaporama" << endl;

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
     _posImageCourante = 0;
    }
    cout << nbImages() << " images restantes dans le diaporama." << endl;

}

void LecteurVue::afficher()
{
    if(numDiaporamaCourant()>0){
        cout<<numDiaporamaCourant()<<endl<<nbImages()<<endl<<_posImageCourante<<endl;
        if (nbImages()!=0){
            ui->lRang->setText((QString::number(_diaporama[_posImageCourante]->getRang())));
            ui->lImage->setPixmap(QPixmap(QString::fromStdString(_diaporama[_posImageCourante]->getChemin())));
            ui->lImage->setAlignment(Qt::AlignCenter);
            ui->lCategorie->setText(QString::fromStdString(_diaporama[_posImageCourante]->getCategorie()));
            ui->lTitre->setText((QString::fromStdString(_diaporama[_posImageCourante]->getTitre())));
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
