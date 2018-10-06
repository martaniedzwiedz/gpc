#ifndef REGULATORPID_H
#define REGULATORPID_H

#include "regulator.h"
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>
///////////////
/// \brief RegulatorPID
///klasa służąca do symulowania regulatora PID
///////////////

class RegulatorPID:public regulator
{
public:
    /////////////
    /// \brief RegulatorPID konstruktor
    /// \param wzm wzmocnienie obiektu
    /// \param nTi stała członu całkującego
    /// \param nTd stała członu różniczkującego
    /// \param nB wartość b członu proporcjonalnego, domyślnie 1
    /// \param nN współczynnik stałej różniczkującej rzeczywistej domyślnie 0.01
    /// \param nTp stała proporcjonalna
    /////////////
    RegulatorPID(double wzm, double nTi, double nTd, double nB=1, double nN=0.01, double nTp=1);
    /////////////
    /// \brief symuluj symulacja regulatora PID
    /// \param t generowany sygnał wartości zadanej
    /// \return zwraca sterowanie
    /////////////
    double symuluj(double t) override;
    /////////////
    /// \brief zmianaNastaw służy do zmiany nastaw regulatora
    /// \param k wmocnienie regulatora
    /// \param Ti stała całkowania
    /// \param Td stała różniczkująca
    /// \param b wartość b członu proporcjonalnego
    /// \param N wawrtość n stałej różniczkującej
    /////////////
    void zmianaNastaw(double k, double Ti=0, double Td=0,double b=0,double N=0) override;
    /////////////
    /// \brief update aktualizuje wartość wyjścia i wylicza uchyb
    /// \param wy wartość wyjścia
    /// \return zwraca bieżącą wartość wyjścia po aktualizacji
    /////////////
    void update(double wy) override;
    /////////////
    /// \brief odczytSterowania metoda pozwalająca na odczyt wartości sterowania
    /// \return zwraca wartość sterowania
    /////////////
    double const odczytSterowania() override;
    /////////////
    /// \brief wczytajRegPID wczytuje nastawy z pliku
    /// \return zwraca wskaźnik na obiekt klasy regulator
    /////////////
    static regulator* wczytajRegPID();
    //boost::numeric::ublas::vector<double> getIden() override;
private:
    double k=1,Ti=0,Td=0,Tp=1,b=1,N=0.01,wyjscieP=0,uchybP=0,I=0,D=0, sterowanie=0;
};

#endif // REGULATORPID_H
