#ifndef PETLASTEROWANIA_H
#define PETLASTEROWANIA_H

#include "obiektsiso.h"
#include "regulator.h"
#include "identyfikacja.h"
#include "wielomian.h"

///////////////////////////////////////
/// \brief PetlaSterowania
///klasa umożliwiająca symulację pętli regulacji
//////////////////////////////////
class PetlaSterowania
{
public:
    /////////////
    /// \brief PetlaSterowania konstruktor
    /// \param ObiektSISO* wskaźnik do obiektu klasy ObiektSISO
    /// \param regulator* wskaźnik do obiektu klasy regulator
    /////////////
    PetlaSterowania(ObiektSISO* = 0, regulator* = 0, Identyfikacja *Id = 0);
    /////////////
    /// \brief krokPetli wykonuje jeden krok pętli sterowania
    /////////////
    void krokPetli();
    /////////////
    /// \brief ustawRegulator ustawia wskaźnik na obiekt klasy regulator
    /// \param regulator* wskaźnik do obiektu klasy regulator
    /////////////
    void ustawRegulator(regulator *);
    /////////////
    /// \brief ustawObiekt ustawia wskaźnik na obiekt klasy ObiektSISO
    /// \param ObiektSISO* wskaźnik do obiektu klasy ObiektSISO
    /////////////
    void ustawObiekt(ObiektSISO*);
    /////////////
    /// \brief zmienGenerator ustawia wskaźnik na obiekt klasy GeneratorPodstawowy
    /// \param GeneratorPodstawowy* wskaźnik do obiektu klasy GeneratorPodstawowy
    /////////////
    void zmienGenerator(GeneratorPodstawowy*);
    /////////////
    /// \brief odczytWartosciZadanej służy do odczytu wartości zadanej
    /// \return zwraca aktualną wartość zadaną
    /////////////
    double odczytWartosciZadanej();
    /////////////
    /// \brief odczytSterowania służy do odczytu wartości sterowania
    /// \return zwraca aktualną wartość sterowania
    /////////////
    double odczytSterowania();
    void zmienIdentyfikator(Identyfikacja *id);
    Identyfikacja *getIdenty();

private:
    int time = 0;
    regulator* psReg;
    ObiektSISO* psOb;
    Identyfikacja *myIdent;
};

#endif // PETLASTEROWANIA_H
