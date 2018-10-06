#ifndef REGULATORP_H
#define REGULATORP_H

#include "regulator.h"
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>
///////////////
/// \brief RegulatorP
///klasa służąca do symulowania regulatora P
///////////////
///
class RegulatorP : public regulator
{
public:
    ////////////////////
    /// \brief RegulatorP konstruktor
    /// \param nP wartość P
    ////////////////////
    RegulatorP(double nP);
    ////////////////////
    /// \brief RegulatorP destruktor
    ////////////////////
    ~RegulatorP();
    ////////////////////
    /// \brief zmianaNastaw
    /// metoda służąca do zmiany nastaw danego regulatora
    /// \param k wzmocnienie regulatora P
    /// \return zwraca wywołanie metody generuj dla konkretnego rodzaju generatora
    ////////////////////
    void zmianaNastaw(double k, double=0, double=0,double=0, double=0) override;
    /////////////
    /// \brief symuluj
    /// metoda wirutalna symulująca regulator P, dziedziczona od obiektu SISO
    /// \param a wartość zadana
    /////////////
    double symuluj(double a) override;
    double const odczytSterowania() override;
    static regulator* wczytajRegP();
private:
    double P, sterowanie=0;
};

#endif // REGULATORP_H
