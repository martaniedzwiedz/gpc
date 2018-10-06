#ifndef REGULATOR_H
#define REGULATOR_H

#include "obiektsiso.h"
#include "obserwator.h"
#include "generatordekorator.h"


#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>

///////////////
/// \brief Regulator
///klasa służąca do implementacji regulatorów, po której dziedziczą wszystkie rodzaje
///////////////

class regulator : public ObiektSISO, public Obserwator
{
public:
    /////////////
    /// \brief ~regulator
    /// wirtualny destruktor
    /////////////
    virtual ~regulator();
    /////////////
    /// \brief update
    /// metoda aktualizująca wyjście, dziedziczona od obserwatora
    /// \param wy wartość wyjścia
    /////////////
    void update(double wy) override;
    /////////////
    /// \brief symuluj
    /// metoda wirutalna symulująca regulator, dziedziczona od obiektu SISO, bedzie nadpisywana w kolejnych regulatorach
    /// \param a wartość zadana
    /////////////
    double symuluj(double a) override = 0;
    ////////////////////
    /// \brief generuj
    /// metoda służąca do generowania
    /// \param t czas
    /// \return zwraca wywołanie metody generuj dla konkretnego rodzaju generatora
    ////////////////////
    virtual double generuj(int t);
    ////////////////////
    /// \brief zmianaNastaw
    /// metoda służąca do zmiany nastaw danego regulatora
    /// \param k wzmocnienie regulatora P
    /// \return zwraca wywołanie metody generuj dla konkretnego rodzaju generatora
    ////////////////////
    virtual void zmianaNastaw(double k, double = 0, double = 0, double = 0, double = 0) = 0;
    ////////////////////
    /// \brief aktualizacjaParametrow
    /// metoda dziedziczona od obserwatora
    ////////////////////
    void aktualizacjaParametrow(std::vector<double>, std::vector<double>, double, double, int, int) override;
    ////////////////////
    /// \brief zmianaWartosciZadanej
    /// służy do zmiany wartości zadanej
    /// \param wartość zadana
    ////////////////////
    virtual void zmianaWartosciZadanej(double zadana);
    ////////////////////
    /// \brief odczytWartosciZadanej
    /// służy do odczytu wartości zadanej
    /// \return zwraca obecną wartość zadaną
    ////////////////////
    virtual  double const odczytWartosciZadanej();
    ////////////////////
    /// \brief odczytUchybu
    /// służy do odczytu wartości uchybu regulacji
    /// \return zwraca obecną wartość uchybu
    ////////////////////
    virtual  double const odczytUchybu();
    ////////////////////
    /// \brief odczytWyjsciaOb
    /// służy do odczytu wartość wyjścia
    /// \return zwraca obecną wartość wyjścia
    ////////////////////
    virtual double const odczytWyjsciaOb();
    ////////////////////
    /// \brief stworzGenerator
    /// służy do tworzenia nowego generatora
    /// \param GeneratorPodstawowy* wskaźnik do obiektu klasy GeneratorPodstawowy
    ////////////////////
    void stworzGenerator(GeneratorPodstawowy *);
    ////////////////////
    /// \brief zmienGenerator
    /// służy do zmiany generatora
    /// \param GeneratorPodstawowy* wskaźnik do obiektu klasy GeneratorPodstawowy
    ////////////////////
    void zmienGenerator( GeneratorPodstawowy *ngenerator);
    virtual double const odczytSterowania() = 0;
    static regulator* odczyt_ustawien(bool);
    void uchybpoprzedni();
    double odczytuchybpoprzedni();
protected:
    GeneratorPodstawowy *generator=0;
    double zad=0, uchyb=0, wyjscie=0, uchybP=0;
};

#endif // REGULATOR_H
