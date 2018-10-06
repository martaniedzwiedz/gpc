#ifndef IDENTYFIKACJA_H
#define IDENTYFIKACJA_H

#include "wielomian.h"

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/symmetric.hpp>

using namespace boost::numeric::ublas;

/////////////////////////////////
/// \brief Identyfikacja
///klasa służąca do identyfikacji RMNK
////////////////////////////////

class Identyfikacja
{
public:
    /////////////////////////////////
    /// \brief Identyfikacja
    /// \param stA stopień wielomianuA
    /// \param stB stopień wielomianuB
    /// \param nK wzmocnienie
    /// \param nAlfa wartość współczynnika zapominania
    /// \param nlambd wartość współczynnika wartości początkowej P (>>1)
    ////////////////////////////////
    Identyfikacja(int stA, int stB, int nK, double nA, double nl=1000, double nmaxP=100000, vector<double> startowe={});
    ////////////////////
    /// \brief zmienParamtery
    /// zmienia parametry obiektu klasy Identyfikacja
    /// \param stA stopien wielomianu A
    /// \param stB stopien wielomianu B
    /// \param nK wzmocnienie
    /// \param nA wartość współczynnika zapominania
    /// \param nl wartość współczynnika wartości początkowej P
    ////////////////////
    void zmienParametry(int stA, int stB,int nK,double nA, double nl=1000, double nmaxP=100000);
    ////////////////////
    /// \brief Identyfikuj
    /// funkcja wykonująca jeden krok identyfikacji
    ////////////////////
    void Identyfikuj();
    ////////////////////
    /// \brief zabezpiecz
    /// sprawdza czy maksymalna wartość macierzy (maxM) nie przekroczyła wartości maxP
    /// jeśli tak to dzielo macierz przez sqrt(maxM)
    ////////////////////
     void zabezpiecz(symmetric_matrix<double> &m);
     ////////////////////
     /// \brief toVector
     /// tworzy wektor z wielomianów u i y
     ////////////////////
     void toVector( Wielomian const &U,  Wielomian const &V);
     ////////////////////
     /// \brief ~Identyfikuj
     /// destuktor, usuwa vec
     ////////////////////
    ~Identyfikacja();
     ////////////////////
     /// \brief getU
     /// \return zwraca referencje do wielomianu u
     ////////////////////
     Wielomian& getU();
     ////////////////////
     /// \brief getY
     /// \return zwraca referencje do wielomianu y
     ////////////////////
     Wielomian& getY();
     boost::numeric::ublas::vector<double> getOmega();
     std::vector<double> getA();
     std::vector<double> getB();
     boost::numeric::ublas::vector<double> OmegaOdczyt;
private:
    Wielomian y,u;
    std::vector<vector<double>> VecBA;
    vector<double>  ki, Omega;
    symmetric_matrix<double> P;
    double A=1, l=1000 ,maxP=100000;
    int dA,dB,K;
    vector<double> *vec;
};

#endif // IDENTYFIKACJA_H
