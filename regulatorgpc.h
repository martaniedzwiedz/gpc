#ifndef REGULATORGPC_H
#define REGULATORGPC_H

#include "regulator.h"
#include "identyfikacja.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>

/////////////////////////////////
/// \brief RegulatorGPC
///klasa służąca do symulacji regulatora GPC
////////////////////////////////
class RegulatorGPC : public regulator
{
public:
    /////////////
    /// \brief RegulatorGPC konstruktor
    /// \param nH długość horyzonu predykcji
    /// \param nL długość horyzontu sterowania
    /// \param na współczynnik występujący w inercji 1-rzędu
    /// \param np waga dla sterowania
    /// \param nk opóźnienie w modelu
    /// \param nA stopień wielomianu A
    /// \param nB stopień wielomianu B
    /// \param Id identyfikator
    /////////////
    RegulatorGPC(unsigned int nH, unsigned int nL, double na, double np, unsigned int nk, unsigned int nA, unsigned int nB, Identyfikacja* Id);
    ////////////////////
    /// \brief RegulatorGPC destruktor
    ////////////////////
    ~RegulatorGPC();
    /////////////
    /// \brief update aktualizuje wartość wyjścia i wylicza uchyb
    /// \param wy wartość wyjścia
    /// \return zwraca bieżącą wartość wyjścia po aktualizacji
    /////////////
    void update(double wy) override;
    /////////////
    /// \brief symuluj symulacja regulatora GPC
    /// \param a generowany sygnał wartości zadanej
    /// \return zwraca sterowanie
    /////////////
    double symuluj(double a) override;
    ///funkcja do odwracania macierzy
    template<class T> bool InvertMatrix (const matrix<T>& input, matrix<T>& inverse);
    ////////////////////
    /// \brief generuj
    /// metoda służąca do generowania
    /// \param t czas
    /// \return zwraca wywołanie metody generuj dla konkretnego rodzaju generatora
    ////////////////////
    double generuj(int t) override;
    ///zmienia Identyfikator na podany w parametrze
    void zmienIdentyfikator(Identyfikacja *n);
    ///zwraca identyfikator przez referencje
    Identyfikacja *getIdentyfikator();
    /////////////
    /// \brief odczytSterowania metoda pozwalająca na odczyt wartości sterowania
    /// \return zwraca wartość sterowania
    /////////////
    double const odczytSterowania() override;
    ////////////////////
    /// \brief zmianaNastaw
    /// funkcja pozwalająca na modyfikację nastaw regulatora GPC
    ////////////////////
    void zmianaNastaw(double,double=0, double=0,double=0,double=0) override;
    /////////////
    /// \brief wczytajRegGPC wczytuje nastawy z pliku
    /// \return zwraca wskaźnik na obiekt klasy regulator
    /////////////
    static regulator* wczytajRegGPC();
private:
    unsigned int H, L, k;
    double a, p, sterowanie=0;
    Identyfikacja *Identyfikator; //parametry Identyfiakcji k dB dA a
    Wielomian WielomianH,WielomianU,YOstatnieObiektu,URzeczywiste,UPrzejsciowe,YPrzejsciowe,dURzeczywiste;
    matrix<double> Q,Ixp,P,Pinv;
    vector<double> qtrans,ones,w0,w,y0;
};

#endif // REGULATORGPC_H
