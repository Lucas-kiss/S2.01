#include "diaporama.h"

template<> Diaporama::Diaporama()
{

}

const QString &Diapo::nomDiapo() const
{
    return _nomDiapo;
}

void Diapo::setNomDiapo(const QString &newNomDiapo)
{
    _nomDiapo = newNomDiapo;
}

unsigned int Diapo::posImageCourante() const
{
    return _posImageCourante;
}

void Diapo::setPosImageCourante(unsigned int newPosImageCourante)
{
    _posImageCourante = newPosImageCourante;
}
